cmake_minimum_required(VERSION 2.8.3)
project(pfebreakbot)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs genmsg roslaunch)

roslaunch_add_file_check(launch)

## Declare ROS messages and services
add_service_files(FILES LIDAR.srv MPP.srv SERVO.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

#add_executable(LIDAR_ROS src/LIDAR_ROS.cpp)
#add_executable(MPP_ROS src/MPP_ROS.cpp)
#add_executable(SERVO_ROS src/SERVO_ROS.cpp)
add_executable(Test_IN_ROS src/Test_IN_ROS.cpp)
add_executable(Test_OUT_ROS src/Test_OUT_ROS.cpp)
add_executable(VUE_ROS src/VUE_ROS.cpp)
add_executable(CONTROLEUR_ROS src/CONTROLEUR_ROS.cpp)
add_executable(Test_VUE_ROS src/Test_VUE_ROS.cpp)

#target_link_libraries(LIDAR_ROS ${catkin_LIBRARIES} /usr/local/lib/libwiringPi.so )
#target_link_libraries(MPP_ROS ${catkin_LIBRARIES} /usr/local/lib/libwiringPi.so )
#target_link_libraries(SERVO_ROS ${catkin_LIBRARIES} )
target_link_libraries(Test_IN_ROS ${catkin_LIBRARIES} )
target_link_libraries(Test_OUT_ROS ${catkin_LIBRARIES} )
target_link_libraries(VUE_ROS ${catkin_LIBRARIES} )
target_link_libraries(CONTROLEUR_ROS ${catkin_LIBRARIES} )
target_link_libraries(Test_VUE_ROS ${catkin_LIBRARIES} )

#add_dependencies(LIDAR_ROS pfebreakbot_generate_messages_cpp)
#add_dependencies(MPP_ROS pfebreakbot_generate_messages_cpp)
#add_dependencies(SERVO_ROS pfebreakbot_generate_messages_cpp)
add_dependencies(Test_IN_ROS pfebreakbot_generate_messages_cpp)
add_dependencies(Test_OUT_ROS pfebreakbot_generate_messages_cpp)
add_dependencies(CONTROLEUR_ROS pfebreakbot_generate_messages_cpp)
add_dependencies(VUE_ROS pfebreakbot_generate_messages_cpp)
add_dependencies(Test_VUE_ROS pfebreakbot_generate_messages_cpp)
