#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "pro_upper_controller_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;
extern void reportOverrun(int rateID);

// For Block pro_upper_controller/Platform/Subscribe
extern SimulinkSubscriber<nav_msgs::Odometry, SL_Bus_pro_upper_controller_nav_msgs_Odometry> Sub_pro_upper_controller_41;

// For Block pro_upper_controller/Platform/Subscribe1
extern SimulinkSubscriber<nav_msgs::Path, SL_Bus_pro_upper_controller_nav_msgs_Path> Sub_pro_upper_controller_42;

// For Block pro_upper_controller/Platform/Publish1
extern SimulinkPublisher<geometry_msgs::Twist, SL_Bus_pro_upper_controller_geometry_msgs_Twist> Pub_pro_upper_controller_43;

void slros_node_init(int argc, char** argv);

#endif
