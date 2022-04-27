#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "rosTxTest_mod";
void reportOverrun(int rateID);

// For Block rosTxTest_mod/Publish
SimulinkPublisher<std_msgs::Float64, SL_Bus_rosTxTest_mod_std_msgs_Float64> Pub_rosTxTest_mod_3;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

