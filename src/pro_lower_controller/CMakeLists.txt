cmake_minimum_required(VERSION 3.0.2)
project(pro_lower_controller)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  dynamixel_sdk
  rospy
  roscpp
  joy
  message_generation
)

catkin_package(
)

include_directories(
include
../../../devel/include
${catkin_INCLUDE_DIRS}
)

#add_executable(Ramp_Test 
#src/Ramp_Test.cpp 
#src/include/Platform_M3508.hpp
#)
#target_link_libraries(Ramp_Test 
#${catkin_LIBRARIES})

add_executable(pro_lower_platform 
src/sbus_serial_driver.cpp
src/Platform_control.cpp 
src/include/Platform_M3508.hpp
src/include/Platform_servo.hpp
)
target_link_libraries(pro_lower_platform 
${catkin_LIBRARIES})
