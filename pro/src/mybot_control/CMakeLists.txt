cmake_minimum_required(VERSION 2.8.3)
project(mybot_control)

find_package(catkin REQUIRED COMPONENTS 
roscpp 
rospy
geometry_msgs 
sensor_msgs 
std_msgs
tf
nav_msgs
)

catkin_package(
   #INCLUDE_DIRS include
   CATKIN_DEPENDS roscpp rospy sensor_msgs std_msgs
)

include_directories(arduino/motor_controller)
include_directories(${catkin_INCLUDE_DIRS})

add_executable(base_controller run/base_controller.cpp)
target_link_libraries(base_controller ${catkin_LIBRARIES})
