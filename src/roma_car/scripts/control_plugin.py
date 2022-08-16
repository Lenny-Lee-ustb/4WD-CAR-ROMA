#!/usr/bin/env python3

import rospy
import math
import sys
import tf2_ros

from std_msgs.msg import Header
from std_msgs.msg import Bool
from std_msgs.msg import Float64
from ackermann_msgs.msg import AckermannDrive
from geometry_msgs.msg import Point32
from geometry_msgs.msg import PolygonStamped
from geometry_msgs.msg import Transform
from geometry_msgs.msg import TransformStamped
from nav_msgs.msg import Odometry

#轴距
wheelbase = 0.335
#轮距
wheeltrack = 0.276
#车轮半径
tire_dia = 0.14605
#45度对应弧度
degrees_45 = 0.785398163

# vehicle name
#car_name = str(sys.argv[1])
car_name = "car"

# subscriber topics

#gazebo_odom_topic = '/{}/ground_truth'.format(car_name)
command_topic = '/{}/command'.format(car_name)

# publisher topics

# odom_pub_topic  = '/{}/base/odom'.format(car_name)
# footprint_topic = '/{}/base/footprint'.format(car_name)

# control topics

# LRW_topic   = '/{}/left_rear_wheel_velocity_controller/command'.format(car_name)
# RRW_topic   = '/{}/right_rear_wheel_velocity_controller/command'.format(car_name)
# LFW_topic   = '/{}/left_front_wheel_velocity_controller/command'.format(car_name)
# RFW_topic   = '/{}/right_front_wheel_velocity_controller/command'.format(car_name)
# LSH_topic   = '/{}/left_steering_hinge_position_controller/command'.format(car_name)
# RSH_topic   = '/{}/right_steering_hinge_position_controller/command'.format(car_name)

# frame names

# odom_frame = 'odom'
# base_frame = '{}_base_link'.format(car_name)

# information publishers

# footprint_pub = rospy.Publisher(footprint_topic, PolygonStamped, queue_size = 1)
# odom_pub      = rospy.Publisher(odom_pub_topic, Odometry, queue_size = 1)
# tf_pub        = tf2_ros.TransformBroadcaster()

# control publishers
#（话题名称，消息类型，消息队列长度）
pub_vel_LRW = rospy.Publisher('/ackermann_car/LB_drive_joint_controller/command', Float64, queue_size=1)
pub_vel_RRW = rospy.Publisher('/ackermann_car/RB_drive_joint_controller/command', Float64, queue_size=1)
pub_vel_LFW = rospy.Publisher('/ackermann_car/LF_drive_joint_controller/command', Float64, queue_size=1)
pub_vel_RFW = rospy.Publisher('/ackermann_car/RF_drive_joint_controller/command', Float64, queue_size=1)

pub_pos_LSH = rospy.Publisher('/racecar/left_steering_hinge_position_controller/command', Float64, queue_size=1)
pub_pos_RSH = rospy.Publisher('/racecar/right_steering_hinge_position_controller/command', Float64, queue_size=1)

# footprint parameters

# global seq

# seq = 0
# footprint = PolygonStamped()

# side_A = Point32()
# side_B = Point32()
# side_C = Point32()
# side_D = Point32()
# side_E = Point32()

# [side_A.x, side_A.y, side_A.z] = [-0.1, -0.2,  0.0]
# [side_B.x, side_B.y, side_B.z] = [ 0.5, -0.2,  0.0]
# [side_C.x, side_C.y, side_C.z] = [ 0.6,  0.0,  0.0]
# [side_D.x, side_D.y, side_D.z] = [ 0.5,  0.2,  0.0]
# [side_E.x, side_E.y, side_E.z] = [-0.1,  0.2,  0.0]

# footprint.header.frame_id = base_frame
# footprint.polygon.points  = [side_A, side_B, side_C, side_D, side_E]

# footprint visualizer

# def footprint_visualizer():

#     global seq

#     footprint.header.seq = seq
#     seq = seq + 1
#     footprint.header.stamp = rospy.Time.now()
#     footprint_pub.publish(footprint)

# def odom_callback(data):

#     odom                      = Odometry()
#     odom.header.frame_id      = odom_frame
#     odom.child_frame_id       = base_frame
#     odom.header.stamp         = rospy.Time.now()
#     odom.pose                 = data.pose
#     odom.pose.pose.position.x = odom.pose.pose.position.x 
#     odom.pose.pose.position.y = odom.pose.pose.position.y 
#     odom.twist = data.twist

#     tf = TransformStamped(header         = Header(
#                           frame_id       = odom.header.frame_id,
#                           stamp          = odom.header.stamp),
#                           child_frame_id = odom.child_frame_id,
#                           transform      = Transform(
#                           translation    = odom.pose.pose.position,
#                           rotation       = odom.pose.pose.orientation))

#     # visualize footprint everytime odom changes

#     footprint_visualizer()

#     odom_pub.publish(odom)
#     tf_pub.sendTransform(tf)

# command variables

# global previous_speed

# previous_speed   = 0.0
# min_speed        = 0.0
# max_speed        = 15.0  # 100.0
# speed_delta      = 1.0 # 1.25
# previous_speed   = 0.0

# command callback


def in_out(sita_in):
    sita_out = abs(math.atan(1/(1/math.tan(abs(sita_in))+wheeltrack/wheelbase)))
    return sita_out

# data消息类型：ackermann_msgs/AckermannDrive
# 消息结构：
# float32 steering_angle
# float32 steering_angle_velocity
# float32 speed
# float32 acceleration
# float32 jerk
def command_callback(data):
    if data.speed > 0:
        w = abs(data.steering_angle_velocity)
    if data.speed < 0:
        w = -abs(data.steering_angle_velocity)

    #左、右轮转向装置角度
    steering_angle_l = Float64()
    steering_angle_r = Float64()
    #四个车轮速度
    speed_lr = Float64()
    speed_rr = Float64()
    speed_lf = Float64()    
    speed_rf = Float64()

    if  data.steering_angle > 0 :
        #转向半径=速度/角速度
        radius = abs(data.speed / data.steering_angle_velocity)
        steering_angle_l = data.steering_angle

        if(abs(steering_angle_l) >= degrees_45):
            steering_angle_l = degrees_45

        steering_angle_r = in_out(steering_angle_l)
        speed_lr = w * (radius - wheeltrack/2) * 2/ tire_dia
        speed_rr = w * (radius + wheeltrack/2) * 2/ tire_dia
        speed_lf = w * wheelbase / math.sin(steering_angle_l) * 2/ tire_dia
        speed_rf = w * wheelbase / math.sin(steering_angle_r) * 2/ tire_dia

    if  data.steering_angle < 0 :
        radius = abs(data.speed / data.steering_angle_velocity)
        steering_angle_r = data.steering_angle

        if(abs(steering_angle_r) >= degrees_45):
            steering_angle_r = -degrees_45

        steering_angle_l = -in_out(steering_angle_r)
        speed_lr = w * (radius + wheeltrack/2) * 2/ tire_dia
        speed_rr = w * (radius - wheeltrack/2) * 2/ tire_dia
        speed_lf = w * wheelbase / math.sin(abs(steering_angle_l)) * 2/ tire_dia
        speed_rf = w * wheelbase / math.sin(abs(steering_angle_r))  * 2/ tire_dia
   
    if  data.steering_angle == 0 :
        steering_angle_l = 0
        steering_angle_r = 0
        #得到轮胎角速度
        speed_lr = data.speed * 2/ tire_dia
        speed_rr = data.speed * 2/ tire_dia
        speed_lf = data.speed * 2/ tire_dia
        speed_rf = data.speed * 2/ tire_dia

    pub_vel_LRW.publish(speed_lr)
    pub_vel_RRW.publish(speed_rr)
    pub_vel_LFW.publish(speed_lf)
    pub_vel_RFW.publish(speed_rf)

    pub_pos_LSH.publish(steering_angle_l)
    pub_pos_RSH.publish(steering_angle_r)
    # speed_lr          = data.speed*15 #* max_speed



    # acceleration_factor = speed_delta

    # if not speed.data == 0.0:
    #     speed_dir = speed.data/abs(speed.data)
    #     speed.data = abs(speed.data)
    # else:
    #     if previous_speed < 0.0:
    #         speed_dir = -1.0
    #     else:
    #         speed_dir = 1.0

    # previous_speed = abs(previous_speed)

    # if speed.data >= previous_speed + acceleration_factor:
    #     speed.data = previous_speed + acceleration_factor
    # elif speed.data <= previous_speed - acceleration_factor:
    #     speed.data = previous_speed - acceleration_factor

    # if speed.data > max_speed:
    #     speed.data = max_speed
    # elif speed.data < min_speed:
    #     speed.data = min_speed

    # speed.data     = speed_dir * speed.data
    # previous_speed = speed.data 



if __name__ == '__main__':

    try:
        rospy.init_node('control_plugin', anonymous = True)
        #rospy.Subscriber(gazebo_odom_topic, Odometry, odom_callback)
        rospy.Subscriber(command_topic, AckermannDrive, command_callback)

        rospy.spin()

    except rospy.ROSInterruptException:

        pass