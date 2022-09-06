#!/bin/bash
source /opt/ros/noetic/setup.bash
source /home/car/4WD-CAR-ROMA/devel/setup.bash
rosbag record -o alpha-underground /odometry/filtered /M3508_Rx_State /Servo_Rx_State /camera/accel/sample /camera/gyro/sample 
