#include "include/upper_controller.hpp"

double last_d_theta = 0;
double last_lateral_dist = 0;
double last_speed = 0;
double P_Yaw, I_Yaw, D_Yaw;
double P_Lateral, I_Lateral, D_Lateral;
double P_Long, I_Long, D_Long,forward_dist;
double Kp, Kd;
double zero_pos,roll_rot_factor,roll_lat_factor,velocity_factor,P_pit,D_pit,P_rol,D_rol;

UpperController::UpperController() {
  // Private parameters handler
  ros::NodeHandle pn("~");

  // Controller parameter
  pn.param("controller_freq", controller_freq, 20.0);
  pn.param("baseSpeed", baseSpeed, 0.0);
  pn.param("goalRadius", goalRadius, 1.0);
  pn.param("goal_pose_err", goal_pose_err, 1.0);
  pn.param("forward_dist", forward_dist, 1.0);
  pn.param("rot_angle", rot_angle, 0.0);
  pn.param("P_Yaw", P_Yaw, 1.0);
  pn.param("I_Yaw", I_Yaw, 0.0);
  pn.param("D_Yaw", D_Yaw, 1.0);
  pn.param("P_Lateral", P_Lateral, 1.0);
  pn.param("I_Lateral", I_Lateral, 1.0);
  pn.param("D_Lateral", D_Lateral, 1.0);
  pn.param("P_Long", P_Long, 1.0);
  pn.param("I_Long", I_Long, 1.0);
  pn.param("D_Long", D_Long, 1.0);

  // Publishers and Subscribers
  odom_sub = n_.subscribe("/odometry/filtered", 1, &UpperController::odomCB, this);

  path_sub = n_.subscribe("/fix_path", 1,
                          &UpperController::pathCB, this);
  goal_sub =
      n_.subscribe("/move_base_simple/goal", 1, &UpperController::goalCB, this);

  marker_pub = n_.advertise<visualization_msgs::Marker>("/car_path", 10);

  pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

  // Timer
  timer1 = n_.createTimer(ros::Duration((1.0) / controller_freq),
                          &UpperController::controlLoopCB,
                          this); // Duration(0.05) -> 20Hz
  timer2 = n_.createTimer(ros::Duration((1.0) / controller_freq),
                          &UpperController::goalReachingCB,
                          this); // Duration(0.05) -> 20Hz

  // Init variables
  goal_received = false;
  goal_reached = false;
  cmd_vel.linear.x = 0;
  cmd_vel.linear.y = 0;
  cmd_vel.angular.z = 0;

  // Show param info
  ROS_INFO("[param] controller_freq: %.2f", controller_freq);
  ROS_INFO("[param] goalRadius: %.2f", goalRadius);
  ROS_INFO("[param] goal_pose_err: %.2f", goal_pose_err);

  ROS_INFO("[param] baseSpeed: %.2f", baseSpeed);
  ROS_INFO("[param] forward_dist: %.2f", forward_dist);
  ROS_INFO("[param] rot_angle: %.2f", rot_angle);
  ROS_INFO("[param] P_Yaw: %.2f", P_Yaw);
  ROS_INFO("[param] I_Yaw: %.2f", I_Yaw);
  ROS_INFO("[param] D_Yaw: %.2f", D_Yaw);
  ROS_INFO("[param] P_Lateral: %.2f", P_Lateral);
  ROS_INFO("[param] I_Lateral: %.2f", I_Lateral);
  ROS_INFO("[param] D_Lateral: %.2f", D_Lateral);
  ROS_INFO("[param] P_Long: %.2f", P_Long);
  ROS_INFO("[param] I_Long: %.2f", I_Long);
  ROS_INFO("[param] D_Long: %.2f", D_Long);

  // Visualization Marker Settings
  initMarker();
}

void UpperController::controlLoopCB(const ros::TimerEvent &) {

  geometry_msgs::Pose carPose = odom.pose.pose;
  geometry_msgs::Twist carVel = odom.twist.twist;
  geometry_msgs::Pose LateralPose = getTrackPose(carPose);
  geometry_msgs::Pose ForwardPose = getTrackForwardPose(carPose,forward_dist);
  double LateralDir = GetLateralDir(carPose, LateralPose);
  double rot_rad = rot_angle / 180.0 * PI;
  double vt,vn,w;
  // double LeftorRight = isRightorLeft(LateralPose.position, carPose);
  lateral_dist = LateralDir * getLateralDist(carPose, LateralPose);

  cmd_vel.linear.x = 0;
  cmd_vel.linear.y = 0;
  cmd_vel.angular.z = 0;

  if (goal_received) {
    double thetar = getYawFromPose(carPose);
    double theta = getYawFromPose(ForwardPose);
    double d_theta = theta - thetar;
    double slow_factor = 1.0- fabs(pow(d_theta/3.14,3));


    if (foundForwardPt) {
        if (!goal_reached) {
          // PID control
          // w = atan2(2*0.35*sin(d_theta),forward_dist);
          w = d_theta + atan2(lateral_dist, carVel.linear.x); 
          vt = baseSpeed;
          
          last_speed = baseSpeed - carVel.linear.x;
          last_d_theta = d_theta;
          last_lateral_dist = lateral_dist;
          
          // Rot_angle
          cmd_vel.angular.z = w;
          cmd_vel.linear.x = vt;

          ROS_INFO("----------");
          ROS_INFO("Vyaw:%.2f, Vt:%.2f",w,vt);
        }
    }
    pub_.publish(cmd_vel);
  }else{
    cmd_vel.angular.z = 0;
    cmd_vel.linear.y = 0;
    cmd_vel.linear.x = 0;
    pub_.publish(cmd_vel);
  }
}

/*****************/
/* MAIN FUNCTION */
/*****************/
int main(int argc, char **argv) {
  // Initiate ROS
  ros::init(argc, argv, "UpperController");
  UpperController controller;
  ros::spin();
  return 0;
}