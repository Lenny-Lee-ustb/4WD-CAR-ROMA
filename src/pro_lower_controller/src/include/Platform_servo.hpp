#include "dynamixel_sdk/dynamixel_sdk.h" 

// Control table address
#define ADDR_PRO_TORQUE_ENABLE          64 // Control table address is different in Dynamixel model
#define ADDR_PRO_GOAL_POSITION          116
#define ADDR_PRO_PRESENT_POSITION       132
#define ADDR_PRO_PRESENT_CURRENT       126


// Data Byte Length
#define LEN_PRO_GOAL_POSITION            4
#define LEN_PRO_PRESENT_POSITION         4

// Protocol version
#define PROTOCOL_VERSION                2.0                 // See which protocol version is used in the Dynamixel

// Default setting
#define BAUDRATE                        4000000
#define DEVICENAME                     "/dev/servo"      // Check which port is being used on your controller

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque

#define DXL_FL_ID                          0                   // Dynamixel#Fl ID: 0
#define DXL_FL_MINIMUM_POSITION_VALUE      1155             // FL ID 0  MIN
#define DXL_FL_MID_POSITION_VALUE          1510             // FL ID 0  MIDDLE
#define DXL_FL_MAXIMUM_POSITION_VALUE      1920              // FL ID 0  MAX

#define DXL_FR_ID                          1                   // Dynamixel#Fr ID: 1
#define DXL_FR_MINIMUM_POSITION_VALUE      1524             // FR ID 1  MIN
#define DXL_FR_MID_POSITION_VALUE          2000             // FR ID 1  MIDDLE
#define DXL_FR_MAXIMUM_POSITION_VALUE      2470              // FR ID 1  MAX

#define DXL_RESOLUTION                     4096 // resolution of the servo

#define DXL_MOVING_STATUS_THRESHOLD     20                  // Dynamixel moving status threshold


struct DynamixelServo
{   

    int32_t posRx, posTx;
    double posNow, posTarget;
    int16_t curRx;
};

