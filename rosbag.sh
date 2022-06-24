#!/bin/bash
source /opt/ros/noetic/setup.bash
source /home/car/4WD-CAR-ROMA/devel/setup.bash
rosbag record -o corner-h /odometry/filtered /M3508_Rx_State
