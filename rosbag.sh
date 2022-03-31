#!/bin/bash
source /opt/ros/noetic/setup.bash
source /home/roma/asoc-roma/devel/setup.bash
rosbag record -o corner-h /odometry/filtered /M3508_Rx_State
