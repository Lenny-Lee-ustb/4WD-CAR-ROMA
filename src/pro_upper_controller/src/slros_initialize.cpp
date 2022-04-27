#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "pro_upper_controller";
void reportOverrun(int rateID);

// For Block pro_upper_controller/Platform/Subscribe
SimulinkSubscriber<nav_msgs::Odometry, SL_Bus_pro_upper_controller_nav_msgs_Odometry> Sub_pro_upper_controller_41;

// For Block pro_upper_controller/Platform/Subscribe1
SimulinkSubscriber<nav_msgs::Path, SL_Bus_pro_upper_controller_nav_msgs_Path> Sub_pro_upper_controller_42;

// For Block pro_upper_controller/Platform/Publish1
SimulinkPublisher<geometry_msgs::Twist, SL_Bus_pro_upper_controller_geometry_msgs_Twist> Pub_pro_upper_controller_43;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

