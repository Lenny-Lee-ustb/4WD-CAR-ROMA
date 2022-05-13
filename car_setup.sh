#!/bin/bash
source /opt/ros/noetic/setup.bash
source /home/car/4WD-CAR-ROMA/devel/setup.bash

cd /home/car/4WD-CAR-ROMA
./spawn_can.sh
./spawn_servo.sh

roslaunch pro_lower_controller pro_platform.launch

read varname