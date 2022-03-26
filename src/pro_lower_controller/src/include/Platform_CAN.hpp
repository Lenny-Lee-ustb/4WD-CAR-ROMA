#include <ros/ros.h>
#include <unistd.h>

#include <chrono>
#include <thread>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PolygonStamped.h>

#define PI 3.14159265

int stopFlag = 0;

struct Motor3508
{
    int16_t curRx, velRx, angleRx, curTx, velTx;
    int8_t thermalRx;

    double targetSpeed, lastSpeed, Speed;

};

void M3508_SendZero(int s)
{
	int nbytes;
    can_frame frame;
	frame.can_id = 0x200;
	frame.can_dlc = 8;
    for(int i=0; i<4; i++){
        frame.data[2*i] = 0;
        frame.data[2*i+1] = 0;
    }
	nbytes = write(s, &frame, sizeof(struct can_frame));

	if (nbytes == -1)
	{
		printf("send error\n");
	}
}


void signalCallback(int signum)
{	
	stopFlag = 1;
	ros::Duration(1.0).sleep();
	ROS_INFO("shutdown!!");
	exit(1);
}