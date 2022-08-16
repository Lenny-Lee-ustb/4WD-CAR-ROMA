cmake_minimum_required(VERSION 2.8.3)

project(roma_car)

find_package(catkin REQUIRED)

catkin_package()

find_package(roslaunch)

foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)

catkin_install_python(PROGRAMS
	scripts/control_plugin.py
	DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# catkin_install_python(PROGRAMS
# 	scripts/test1.py
# 	DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )