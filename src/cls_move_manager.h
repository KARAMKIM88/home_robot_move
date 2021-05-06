#pragma once

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <thread>


enum State{
        STATE_IDLE,
        STATE_GOAL,
        STATE_MONITORING //future work
};

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class cls_move_manager{

public:
    cls_move_manager(){

        assign_control_value();
        
        velocity_ctl = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
        
        
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
    static bool subs_flags;

    ros::NodeHandle nh;
    ros::Subscriber ga_state_manager;
    MoveBaseClient* ac;
    ros::Publisher position_ctl;
    ros::Publisher velocity_ctl;
    move_base_msgs::MoveBaseGoal goal;
    geometry_msgs::Twist stop_msg;
    
private :

    static void google_assistant_callback(const std_msgs::String::ConstPtr& msg);
    void assign_control_value()
    {
        stop_msg.linear.x = 0;
        stop_msg.linear.y = 0;
        stop_msg.angular.z = 0;

        goal.target_pose.header.frame_id = "base_link";
        goal.target_pose.header.stamp = ros::Time::now();
        goal.target_pose.pose.position.x = 1.0;
        goal.target_pose.pose.orientation.w = 1.0;

    };

    void control_turtlebot();








};