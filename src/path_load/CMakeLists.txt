cmake_minimum_required(VERSION 3.0.2)
project(path_load)
find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
  std_msgs
  tf
  geometry_msgs
  nav_msgs
)
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES canTest
#  CATKIN_DEPENDS rospy rpscpp std_msgs
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


