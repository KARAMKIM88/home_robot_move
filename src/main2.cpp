/*
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/String.h>
*/
#include "cls_move_manager.h"






int main(int argc, char** argv){
    ros::init(argc, argv, "home_robot_move");
   
    cls_move_manager move_manager;



    

  //wait for the action server to come up
  
/*
    move_base_msgs::MoveBaseGoal goal;
    ros::Rate loop_rate(10);
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

  
    goal.target_pose.pose.position.x = 0.2;
    goal.target_pose.pose.position.y = 0.5;
    goal.target_pose.pose.orientation.w = 0.0;

    ROS_INFO("test test test");

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

    return 0;
}