#include "cls_move_manager.h"


int cls_move_manager::my_state = STATE_IDLE;


void cls_move_manager::google_assistant_callback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("I heard : [%s]", msg->data.c_str());

    if(my_state == STATE_MONITORING){
        //send goal cancel
        my_state = STATE_IDLE;
        ROS_INFO("my state change MONITERING TO IDLE");
    }
    if(my_state == STATE_IDLE){

    }

}
