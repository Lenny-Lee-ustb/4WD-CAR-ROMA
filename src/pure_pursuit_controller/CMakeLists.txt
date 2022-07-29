cmake_minimum_required(VERSION 3.0.2)
project(pure_pursuit_controller)

find_package(catkin REQUIRED COMPONENTS
roscpp
rospy  
dynamic_reconfigure
std_msgs
tf
geometry_msgs
nav_msgs
visualization_msgs
std_msgs
tf
)

catkin_package(
  CATKIN_DEPENDS visualization_msgs
)

include_directories(
  # include
  ${catkin_INCLUDE_DIRS}
)


add_executable(upper_controller_angle 
src/upper_controller_angle.cpp
src/include/upper_controller.hpp)
target_link_libraries(upper_controller_angle
  ${catkin_LIBRARIES}
)