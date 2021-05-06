#include "cls_move_manager.h"

int cls_move_manager::my_state = STATE_IDLE;
bool cls_move_manager::subs_flags = false;

/*

    while(ros::ok()){
        
        if(my_state == STATE_GOAL){
            ac.sendGoal(goal);
            ac.waitForResult();

            if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
                my_state = STATE_IDLE;
                ROS_INFO("Hooray, the base moved 1 meter forward");
            }else{
                ROS_INFO("The base failed to move forward 1 meter for some reason");
            }
        }   
        
        ros::spinOnce();
    }




*/

void cls_move_manager::google_assistant_callback(const std_msgs::String::ConstPtr &msg)
{
    ROS_INFO("I heard : [%s]", msg->data.c_str());

    if (my_state == STATE_MONITORING)
    {
        //send goal cancel
        subs_flags == true;

        
    }
    if (my_state == STATE_IDLE)
    {
        subs_flags = true;
    }
}

void cls_move_manager::control_turtlebot()
{

    while (ros::ok())
    {

        if (my_state == STATE_MONITORING && subs_flags == true)
        {

            ROS_INFO("my state change MONITERING TO IDLE");
            velocity_ctl.publish(stop_msg);
            my_state = STATE_IDLE;
            subs_flags = false;
        }
        else if (my_state == STATE_IDLE && subs_flags == true)
        {
            ac->sendGoal(goal);
            ac->waitForResult();

            if (ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
            {
                my_state = STATE_GOAL;
                ROS_INFO("Hooray, the base moved 1 meter forward");
            }
            else
                ROS_INFO("The base failed to move forward 1 meter for some reason");

            subs_flags = false;
        }

        ros::spinOnce();
    }
}