# include"include/Platform_M3508.hpp"
# include"include/Platform_servo.hpp"
#include "include/sbus_serial_driver.h"
#include "include/Sbus.h"

#define CAR_LENGTH 0.404 //m
#define CAR_WIDTH 0.281 //m
#define MAX_STEER 0.8 //rad
#define MIN_STEER -0.8 //rad
#define MOTOR_RATIO 5.18 // input/output
#define WHEEL_RADIUS 0.07 // wheel radius of 1/10 car
#define WHEEL_OFFSET 0.03 //m
#define MAX_SPPED 5.0 // 12.0m/s at 9000rpm
#define MIN_SPPED -1.0 // 12.0m/s at 9000rpm

ros::Publisher motorInfoPub, servoInfoPub;
ros::Subscriber simulinkSub, sbusSub;
geometry_msgs::PolygonStamped MotorInfo, ServoInfo;
geometry_msgs::Twist cmdUp, cmdSbus;
sensor_msgs::Temperature MotorTemp;

double temp, tempLast, tempAlpha = 0.05;
double speedMax = 0.0, speedMin = -0.0;
double frictionTor = 0.020;
double vt_cmd,delta_cmd;

int  moveable_in, direct_in, control_in = 0;
bool failsafe, frame_lost = 0;

Motor3508 motor[4];
DynamixelServo servo[2];

void sbusCB(const sbus_serial::Sbus::ConstPtr& sbus){
    int deadband_speed = 30;
    int deadband_steer = 5;
    int speedSbusIn, steerSbusIn = 0; // from upper controller   

    speedSbusIn = sbus->mappedChannels[2];
    steerSbusIn = sbus->mappedChannels[3] - 500;
    // remap steer angle to symatric[-500, 500]
    moveable_in = sbus->mappedChannels[6];
    direct_in = sbus->mappedChannels[7];
    control_in = sbus->mappedChannels[9];
    failsafe = sbus->failsafe;
    frame_lost = sbus->frame_lost;
    // signal inout and store

    if (speedSbusIn - deadband_speed <= 0)
        {
            cmdSbus.linear.x = 0;
        }
        else
        {
            if(direct_in<500){
                cmdSbus.linear.x = double(speedSbusIn - deadband_speed)/double(1000 - deadband_speed) * speedMax;
            }
            else if(direct_in>500){
                cmdSbus.linear.x = double(speedSbusIn - deadband_speed)/double(1000 - deadband_speed) * speedMin;
            }
        }
        cmdSbus.angular.z = -double(steerSbusIn) / 500 * MAX_STEER;
}

void cmdCB(const geometry_msgs::Twist::ConstPtr &cmd_vel){
    cmdUp = *cmd_vel;
}

void CmdMux(){

    if ( (!moveable_in == !control_in) || failsafe == 1 || frame_lost == 1){
        vt_cmd = 0.0;
        delta_cmd = 0.0;
        if (failsafe == 1 || frame_lost == 1){
            ROS_ERROR("RC SIGNAL LOST!!! Check RC status!");
        }
        else{
            // ROS_ERROR("RC NOT enable, please toggle SWA to down!!");
            ROS_WARN("moveable_in=%d, control_in=%d", !!moveable_in, !!control_in);
        }
        // ROS_WARN("input speed is: %lf, %d", vt_cmd, speedSbusIn);
        // ROS_WARN("input steer is: %lf, %d", delta_cmd, steerSbusIn);
    }
    else{
        if (!moveable_in == false)
        {
            vt_cmd = cmdSbus.linear.x;
            delta_cmd = cmdSbus.angular.z;
        }
        if (!control_in == false)
        {
            vt_cmd = cmdUp.linear.x;
            delta_cmd = cmdUp.angular.z;
        }
        
        // ROS_INFO("input speed is: %lf, %d", vt_cmd, speedSbusIn);
        // ROS_INFO("input steer is: %lf, %d", delta_cmd, steerSbusIn);
    }
}

// INPUT: vt(m/s),deltaF(rad) 
// OUTPUT: 4WID-AFIS
void BodytoWheel(double vt, double deltaF){
    double R, deltaFL, deltaFR, vFL, vFR, vRL, vRR; // variable for ackermann

    deltaF = fmin(fmax(deltaF,MIN_STEER),MAX_STEER);
    vt = fmin(fmax(vt,speedMin),speedMax);

    // ackermann relation
    R = CAR_LENGTH / (tan(deltaF)+1e-9);
    if (R>=0){
        deltaFL = atan2(CAR_LENGTH,R-CAR_WIDTH/2);
        deltaFR = atan2(CAR_LENGTH,R+CAR_WIDTH/2);
    }
    else if (R<0){
        deltaFL = atan2(CAR_LENGTH,R-CAR_WIDTH/2)-PI;
        deltaFR = atan2(CAR_LENGTH,R+CAR_WIDTH/2)-PI;
    }
    vFL = (CAR_LENGTH/sin(deltaFL)-WHEEL_OFFSET)*vt/R;
    vFR = (CAR_LENGTH/sin(deltaFR)+WHEEL_OFFSET)*vt/R;
    vRL = (R-CAR_WIDTH/2-WHEEL_OFFSET)*vt/R;
    vRR = (R+CAR_WIDTH/2+WHEEL_OFFSET)*vt/R;

    servo[0].posTarget = deltaFL;
    servo[0].posTx = (int) (servo[0].posTarget * (DXL_RESOLUTION/ (2*PI)) + DXL_FL_MID_POSITION_VALUE);
    servo[0].posTx = std::min(std::max(servo[0].posTx,DXL_FL_MINIMUM_POSITION_VALUE),DXL_FL_MAXIMUM_POSITION_VALUE);
    servo[1].posTarget = deltaFR;
    servo[1].posTx = (int) (-servo[1].posTarget * (DXL_RESOLUTION/ (2*PI)) + DXL_FR_MID_POSITION_VALUE);
    servo[1].posTx = std::min(std::max(servo[1].posTx,DXL_FR_MINIMUM_POSITION_VALUE),DXL_FR_MAXIMUM_POSITION_VALUE);

    // ROS_INFO("R: %.2f, FL: %.2f, FR: %.2f, ", R, deltaFL, deltaFR);
    // ROS_INFO("FL-int: %d, FR-int: %d, ", servo[0].posTx, servo[1].posTx);

    motor[0].speedDes = vFL;
    motor[1].speedDes = -vFR;
    motor[2].speedDes = -vRR;
    motor[3].speedDes = vRL;
    motor[0].torDes = motor[0].torConst;
    motor[1].torDes = -motor[1].torConst;
    motor[2].torDes = -motor[2].torConst;
    motor[3].torDes = motor[3].torConst;
    // ROS_INFO("FL: %.2f, FR: %.2f, RL: %.2f, RR: %.2f", vFL,vFR,vRL,vRR);

    for (int i = 0; i < 4; i++)
    {
        motor[i].curTx = MotorTune(motor[i]);
        // ROS_INFO("[%d]: %d",i,motor[i].curTx);
    };
}


void rxMotorThread(int s){
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
            motor[ID].speed = WHEEL_RADIUS * (motor[ID].velRx / MOTOR_RATIO) * (2.0 * PI/60.0);
            motor[ID].tor = K * motor[ID].curRx / 16384.0 * 20.0;

            motor[ID].speedF = LowPassFilter(motor[ID], motor[ID].speedF_Last, motor[ID].speed, motor[ID].speedLast);
            motor[ID].torF = LowPassFilter(motor[ID], motor[ID].torF_Last, motor[ID].tor, motor[ID].torLast);

            MotorTemp.temperature = double(motor[ID].thermalRx) *(1-tempAlpha) + tempLast* tempAlpha ;
            tempLast = MotorTemp.temperature;
            motor[ID].speedLast = motor[ID].speed;
            motor[ID].speedF_Last = motor[ID].speedF;
            motor[ID].torLast = motor[ID].tor;
            motor[ID].torF_Last = motor[ID].torF;

            // due to the configuration, it needs change the direction
            if ((ID==1) || (ID==2))
            {
                MotorInfo.polygon.points[ID].x = -motor[ID].speedF;
                MotorInfo.polygon.points[ID].y = -motor[ID].torF; 
                MotorInfo.polygon.points[ID].z = MotorTemp.temperature;
            }
            else if ((ID==0) || (ID==3))
            {
                MotorInfo.polygon.points[ID].x = motor[ID].speedF; // m/s
                MotorInfo.polygon.points[ID].y = motor[ID].torF;  // -16384~0~16384 -> -20-0-20A -> -1.626 - 1.626Nm
                MotorInfo.polygon.points[ID].z = MotorTemp.temperature;  // 'c
            }
        }
        if(i%4==0){
        motorInfoPub.publish(MotorInfo);
        }
		std::this_thread::sleep_for(std::chrono::nanoseconds(10000));
    }
}


void txMotorThread(int s)
{
    struct can_frame frame;
	frame.can_id = 0x200;
	frame.can_dlc = 8;

    for (int i = 0;; i++) 
	{
        int nbytes;
        CmdMux();
        vt_cmd = fmin(fmax(vt_cmd,speedMin),speedMax);
        BodytoWheel(vt_cmd,delta_cmd);

        if(stopFlag == 0){
            for (int j = 0; j < 4; j++) 
            {
                frame.data[2*j] = motor[j].curTx>>8; //?????????????????? 8 ???
                frame.data[2*j+1] = motor[j].curTx>>0; //?????????????????? 8 ???
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
        // if (i%100==0)
        // {
        //     ROS_INFO("[0]:%d,[1]:%d,[2]:%d,[3]:%d",motor[0].curTx, motor[1].curTx, motor[2].curTx, motor[3].curTx);
        // }
        
		std::this_thread::sleep_for(std::chrono::nanoseconds(1000000)); 
    }
    
};

int rxtxServoThread(){
    // Dynamixel init
    dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    int index = 0; 
    int dxl_comm_result = COMM_TX_FAIL;             // Communication result
    bool dxl_addparam_result = false;               // AddParam result
    bool dxl_getdata_result = false;                // GetParam result
    int dxl_fl_position_lim[2] = {DXL_FL_MINIMUM_POSITION_VALUE, DXL_FL_MAXIMUM_POSITION_VALUE}; // limit position
    int dxl_fr_position_lim[2] = {DXL_FR_MINIMUM_POSITION_VALUE, DXL_FR_MAXIMUM_POSITION_VALUE}; // limit position
    uint8_t dxl_error = 0; // Dynamixel error
    uint8_t param_goal_position[4]; 

    // open port
    if (portHandler->openPort()){
        printf("Succeeded to open the port!\n");
    }
    else{
        printf("Failed to open the port!\n");
    }
    // Set port baudrate
    if (portHandler->setBaudRate(BAUDRATE)){
        printf("Succeeded to change the baudrate!\n");
    }
    else{
        printf("Failed to change the baudrate!\n");
    }
    // Enable Dynamixel#DXL_FL_ID Torque
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_FL_ID, ADDR_PRO_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
        ROS_WARN("dxl_comm_result: %d",dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
        ROS_WARN("dxl_error: %d",dxl_error);
    }
    else
    {
        ROS_INFO("Dynamixel#%d has been successfully connected \n", DXL_FL_ID);
    }
    // Enable Dynamixel#DXL_FR_ID Torque
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_FR_ID, ADDR_PRO_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
        ROS_WARN("dxl_comm_result: %d",dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
        ROS_WARN("dxl_error: %d",dxl_error);
    }
    else
    {
        ROS_INFO("Dynamixel#%d has been successfully connected \n", DXL_FR_ID);
    }

    for (int i = 0;; i++)
    {
        if (stopFlag ==0){
            if (i%5==0){
                //read first
                

                // read position
                dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_FL_ID, ADDR_PRO_PRESENT_POSITION, (uint32_t*)&servo[0].posRx, &dxl_error);
                if (dxl_comm_result != COMM_SUCCESS)
                    {
                        ROS_WARN("dxl_comm_result: %d",dxl_comm_result);
                    }
                    else if (dxl_error != 0)
                    {
                        ROS_WARN("dxl_error: %d",dxl_error);
                    }
                dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, DXL_FR_ID, ADDR_PRO_PRESENT_POSITION, (uint32_t*)&servo[1].posRx, &dxl_error);
                if (dxl_comm_result != COMM_SUCCESS)
                    {
                        ROS_WARN("dxl_comm_result: %d",dxl_comm_result);
                    }
                    else if (dxl_error != 0)
                    {
                        ROS_WARN("dxl_error: %d",dxl_error);
                    }
                
                // read current 
                dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, DXL_FL_ID, ADDR_PRO_PRESENT_CURRENT, (uint16_t*)&servo[0].curRx, &dxl_error);
                if (dxl_comm_result != COMM_SUCCESS)
                    {
                        ROS_WARN("dxl_comm_result: %d",dxl_comm_result);
                    }
                    else if (dxl_error != 0)
                    {
                        ROS_WARN("dxl_error: %d",dxl_error);
                    }
                dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, DXL_FR_ID, ADDR_PRO_PRESENT_CURRENT, (uint16_t*)&servo[1].curRx, &dxl_error);
                if (dxl_comm_result != COMM_SUCCESS)
                    {
                        ROS_WARN("dxl_comm_result: %d",dxl_comm_result);
                    }
                    else if (dxl_error != 0)
                    {
                        ROS_WARN("dxl_error: %d",dxl_error);
                    }
                for (int i = 0; i < 2; i++)
                {
                    ServoInfo.polygon.points[i].x = (float)servo[i].posRx;
                    ServoInfo.polygon.points[i].y = (float)servo[i].curRx;
                }
                // ROS_INFO("[L]cur:%.2f, pos:%.2f.",ServoInfo.polygon.points[0].y, ServoInfo.polygon.points[0].x);
                // ROS_INFO("[R]cur:%.2f, pos:%.2f.",ServoInfo.polygon.points[1].y, ServoInfo.polygon.points[1].x);

                servoInfoPub.publish(ServoInfo);
            }

            // write
            dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_FL_ID, ADDR_PRO_GOAL_POSITION, servo[0].posTx, &dxl_error);
            if (dxl_comm_result != COMM_SUCCESS)
                {
                    ROS_WARN("dxl_comm_result: %d",dxl_comm_result);
                }
                else if (dxl_error != 0)
                {
                    ROS_WARN("dxl_error[%d]: %d",DXL_FL_ID,dxl_error);
                }

            dxl_comm_result = packetHandler->write4ByteTxRx(portHandler, DXL_FR_ID, ADDR_PRO_GOAL_POSITION,servo[1].posTx, &dxl_error);
            if (dxl_comm_result != COMM_SUCCESS)
                {
                    ROS_WARN("dxl_comm_result: %d",dxl_comm_result);
                }
                else if (dxl_error != 0)
                {
                    ROS_WARN("dxl_error[%d]: %d",DXL_FR_ID,dxl_error);
                }
            
        }
        else{
            dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_FL_ID, ADDR_PRO_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
            dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_FR_ID, ADDR_PRO_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
            portHandler->closePort();
            return 0;
        } 
        // set time delay
        
    }
    return 1;
}

int main(int argc, char** argv) {
	int s;
	struct sockaddr_can addr;
	struct ifreq ifr;
    std::string canSeries="can0";

	ros::init(argc,argv,"Pro_platform_controller");
	ros::NodeHandle n("~");
	ros::Rate loop_rate(100);
    sbusSub = n.subscribe<sbus_serial::Sbus>("/sbus", 10, sbusCB);
    simulinkSub = n.subscribe<geometry_msgs::Twist>("/cmd_vel", 10, cmdCB);
    motorInfoPub = n.advertise<geometry_msgs::PolygonStamped>("/M3508_Rx_State", 10);
    servoInfoPub = n.advertise<geometry_msgs::PolygonStamped>("/Servo_Rx_State", 10);
    MotorInfo.polygon.points.resize(4);
    ServoInfo.polygon.points.resize(2);
    
    signal(SIGINT, signalCallback);

    // get param from ros 
    n.getParam("canSeries", canSeries);
    n.getParam("speedMax",speedMax);
    n.getParam("speedMin",speedMin);

    // CAN bus init
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
	std::thread canTx(txMotorThread, s);
	std::thread canRx(rxMotorThread, s);
    std::thread servoRx(rxtxServoThread);

	while (ros::ok())
    {
		ros::spinOnce();
		loop_rate.sleep();
	}

    return 0;
}