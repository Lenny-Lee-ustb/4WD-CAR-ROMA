# Demand for flysky remote control

## An example of receive pack

Ch1: 1102, Ch2: 1100, Ch3: 1306, Ch4: 1100, Ch5: 0240, Ch6: 0240, Ch7: 1024, Ch8: 1024, Ch9: 1024, Ch10: 1024, Ch11: 1024, Ch12: 1024, Ch13: 1024, Ch14: 1024, Ch15: 1024, Ch16: 1024, FS: 0, FL: 0

1. Check the function of 'FS: 0, FL: 0', it may improve the sercurity of remote control. 
2. Map ch1~ch4 values to our command.
3. Command to open sbus node:
    
    roslaunch sbus_serial sbus_serial.launch 