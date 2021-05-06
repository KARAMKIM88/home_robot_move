#pragma once

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/String.h>


enum State{
        STATE_IDLE,
        STATE_GOAL,
        STATE_MONITORING //future work
};

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class cls_move_manager{

public:
    cls_move_manager(){
        
        
        ga_state_manager = nh.subscribe("GA", 10, google_assistant_callback);
        ac = new MoveBaseClient("move_base", true);

        while(!ac->waitForServer(ros::Duration(5.0))){
            ROS_INFO("Waiting for the move_base action server to come up");
        }


    };
    ~ cls_move_manager() {
        delete ac;
    };






private:

    static int my_state ;
    ros::NodeHandle nh;
    ros::Subscriber ga_state_manager;
    MoveBaseClient* ac;


private :

    static void google_assistant_callback(const std_msgs::String::ConstPtr& msg);








};