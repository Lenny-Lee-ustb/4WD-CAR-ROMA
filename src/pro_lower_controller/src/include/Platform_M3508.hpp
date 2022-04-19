#ifdef __linux__
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#endif

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

#include "std_msgs/String.h"
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PolygonStamped.h>
#include <sensor_msgs/Temperature.h>

#define PI 3.14159265
#define K 0.0813  // M3508 5:1 constant N'm/A
#define M3508_T_MAX 1.62
#define M3508_T_MIN -1.62


int stopFlag = 0;

struct Motor3508
{
    int16_t curRx, velRx, angleRx, curTx;
    int8_t thermalRx; // Monitor thermal

	double tor, torLast, torF, torF_Last, torDes, torConst; // tor = K*cur
    double speed, speedLast, speedF, speedF_Last, speedDes, speedErr; // m/s
	double D_speed = 1.0;
	double I_speed = 0.0; // parameter

	double a_1=0.828,b_0=0.086,b_1=0.086;
};

int16_t MotorTune(Motor3508 &m){
	// This method is borrowed from MIT Cheetah, which is used in Tmotor AK series. 
	double Vdes = m.speedDes;
	double dTheta = m.speed;
	double Kd = m.D_speed;
	double T_ff = m.torDes;
	double T_ref;
	int16_t iqref;

	T_ref = Kd * (Vdes-dTheta) + T_ff;
	T_ref = std::min(std::max(T_ref, M3508_T_MIN), M3508_T_MAX);
	iqref = (int16_t) round(T_ref/K*(16384.0/20.0));
	return iqref;
}

double LowPassFilter(Motor3508 &m, double yLast, double x, double xLast){
	// low-pass filter for motor's sensor, ylast is the last estimate value, x is observed value
	double f;
	// y_{n} = a_1 * y_{n-1} + b_0 * x_{n} + b_1 * x_{n-1}
	f = m.a_1 * yLast + m.b_0 * x + m.b_1 * xLast;
	return f;
}

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
	ROS_WARN("Get Ctrl+c signal to shutdwon the node.");
	ros::Duration(3.0).sleep();
	ROS_WARN("shutdown!!");
	exit(1);
}

int getch()
{
#ifdef __linux__
  struct termios oldt, newt;
  int ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
#elif defined(_WIN32) || defined(_WIN64)
  return _getch();
#endif
}