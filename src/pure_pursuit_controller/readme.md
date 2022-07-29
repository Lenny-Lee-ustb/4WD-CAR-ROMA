# asoc_upper_controller
文件结构：\
|--> cfg \
| 存放实时调参的配置文件 \
|--> src \
| include/upper_controller_v2.hpp 上层控制器的一些消息回调函数以及运算函数\
| upper_controller_xxx.cpp 不同版本的上位机控制程序，主要区别在于循迹时的位型\

使用方式：\
roslaunch asoc_upper_controller asoc_base_indoor.launch (启动室内定位和地图加载)\
roslaunch asoc_upper_controller asoc_control_anti.launch （启动上层控制器）\
or\
roslaunch asoc_upper_controller asoc_base_outdoor.launch (启动室外RTK定位和地图加载)\
roslaunch asoc_upper_controller asoc_control_anti.launch （启动上层控制器）



注意事项：\
asoc_base的launch文件中集成了较多功能，有些功能在使用上会有冲突
