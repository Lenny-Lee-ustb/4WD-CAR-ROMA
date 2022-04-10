# Documentation for Dji M3508 
### src/include - directory for head file
Platform_M3508.hpp:  
Motor3508: strucure-> Rx(receive) Tx(Send)  
M3508_SendZero: send zero command  
signalCallback: shutdown the node and set Stopflag  

### src/Ramp_Test.cpp - genrate ramp signal for motor  
Be care of the Motor_ramp in main!!

### src/Platform_control.cpp - lower controller for car
please run it via launch file !!

### Model Parameter
see src/pro_lower_controller/src/include/Platform_M3508.hpp and src/pro_lower_controller/src/include/Platform_servo.hpp

