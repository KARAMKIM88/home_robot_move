
#include "cls_move_manager.h"






int main(int argc, char** argv){
    ros::init(argc, argv, "home_robot_move");
   
    cls_move_manager move_manager;
    move_manager.control_turtlebot();


    ROS_INFO("test test test");


    return 0;
}