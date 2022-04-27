#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "rosTxTest_mod_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;
extern void reportOverrun(int rateID);

// For Block rosTxTest_mod/Publish
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_rosTxTest_mod_std_msgs_Float64> Pub_rosTxTest_mod_3;

void slros_node_init(int argc, char** argv);

#endif
