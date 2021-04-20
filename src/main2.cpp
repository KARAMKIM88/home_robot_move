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

State my_state;


void google_assistant_callback(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("I heard : [%s]", msg->data.c_str());

    if(my_state == STATE_MONITORING){
        //send goal cancel
        my_state = STATE_IDLE;
        ROS_INFO("my state change MONITERING TO IDLE");
    }
    if(my_state == STATE_IDLE){

    }

}


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
    ros::init(argc, argv, "home_robot_move");
    ros::NodeHandle nh;
    ros::Subscriber ga_state_manager = nh.subscribe("GA", 10, google_assistant_callback);

  //tell the action client that we want to spin a thread by default



    MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

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

    return 0;
}