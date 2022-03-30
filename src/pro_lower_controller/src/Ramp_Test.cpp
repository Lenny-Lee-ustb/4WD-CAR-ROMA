# include"include/Platform_CAN.hpp"

ros::Publisher motorInfoPub;
geometry_msgs::PolygonStamped MotorInfo;

Motor3508 motor[4];

void rxThread(int s){
    int ID, nbytes;
    struct can_frame frame;
	frame.can_dlc = 8;


    for (int i = 0;; i++)
    {
		ros::spinOnce();
        nbytes = read(s, &frame, sizeof(struct can_frame));
        if (nbytes < 0){
            perror("Read Error at low can");
            break;
        }
        else if(int(frame.can_id) > 0x200)
        {
            ID = int(frame.can_id - 0x200)-1;
            motor[ID].angleRx = ((frame.data[0]<<8) + frame.data[1]); 
            motor[ID].velRx = (frame.data[2]<<8) + frame.data[3]; 
            motor[ID].curRx = (frame.data[4]<<8) + frame.data[5];  
            motor[ID].thermalRx = frame.data[6]; // 'C
            MotorInfo.polygon.points[ID].x = float(motor[ID].angleRx)/8191.0*360.0; // 0-8191 -> 0-360 degree
            MotorInfo.polygon.points[ID].y = float(motor[ID].velRx);  // rpm
            MotorInfo.polygon.points[ID].z = float(motor[ID].curRx)/16384.0*20.0;  // -16384~0~16384 -> -20-0-20A

        }
        if(i%4==0){
        motorInfoPub.publish(MotorInfo);
        }
		std::this_thread::sleep_for(std::chrono::nanoseconds(10000));
    }
    

}

void txThread(int s)
{
    struct can_frame frame;
	frame.can_id = 0x200;
	frame.can_dlc = 8;

    for (int i = 0;; i++) 
	{
        int nbytes;
        if(stopFlag == 0){
            for (int j = 0; j < 4; j++) 
            {
                frame.data[2*j] = motor[j].curTx>>8; //控制电流值高 8 位
                frame.data[2*j+1] = motor[j].curTx>>0; //控制电流值低 8 位
            }
            nbytes = write(s, &frame, sizeof(struct can_frame));
            if (nbytes == -1) {
                printf("send error\n");
            }
        }
        else if (stopFlag == 1){
            for (int i = 0; i < 8; i++)
            {
                frame.data[i] = 0;
            }
            nbytes = write(s, &frame, sizeof(struct can_frame));
        }
		std::this_thread::sleep_for(std::chrono::nanoseconds(1000000)); 
    }
    
}

void Motor_Ramp(const double& duration, const int16_t maxCur){
    // duration means the ramp time, maxCur is the target current in final
    for (size_t i = 0;i<duration*1000; i++)
    {
        for (int j = 0; j < 4; j++) 
        {
            motor[j].curTx = (maxCur/(duration*1000))*i;
        }
        ROS_INFO("curTx=%d", motor[1].curTx);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000)); //1000hz
    }
}

int main(int argc, char** argv) {
	int s;
	struct sockaddr_can addr;
	struct ifreq ifr;
    std::string canSeries="can0";
    double dt = 10.0;
    int16_t maxcur = 0.05*16384;
    // int16_t maxcur = 16384;

	ros::init(argc,argv,"Ramp_Test");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);
    motorInfoPub = n.advertise<geometry_msgs::PolygonStamped>("M3508_State", 10);
    MotorInfo.polygon.points.resize(4);
    signal(SIGINT, signalCallback);

    n.getParam("canSeries", canSeries);

	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return -1;
	}
	strcpy(ifr.ifr_name, canSeries.c_str());
	ioctl(s, SIOCGIFINDEX, &ifr);

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifr.ifr_name, ifr.ifr_ifindex);

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return -2;
	}
    sleep(1);
	std::thread canTx(txThread, s);
	std::thread canRx(rxThread, s);
    sleep(1);
    Motor_Ramp(dt, maxcur);

	while (ros::ok())
    {
		ros::spinOnce();
		loop_rate.sleep();
	}

    return 0;
}