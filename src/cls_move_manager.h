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

typedef struct _image_coordi
{

    _image_coordi() {};
    _image_coordi(int _x, int _y) : x(_x), y(_y){}
    int x;
    int y;

} image_coordi;




typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class cls_move_manager{

public:
    cls_move_manager(){
         std::locale::global(std::locale("ko_KR.UTF-8"));

        assign_control_value();
        
        velocity_ctl = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
        
        
        ga_state_manager = nh.subscribe("GA", 10, google_assistant_callback);
        ac = new MoveBaseClient("move_base", true);

        while(!ac->waitForServer(ros::Duration(5.0))){
            ROS_INFO("Waiting for the move_base action server to come up");
        }

        ROS_INFO("Setup predefined goals\n");
        set_turtlebot_goal();


    };
    ~ cls_move_manager() {
        delete ac;
    };
    void control_turtlebot();






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

    static constexpr float resolution = 0.05;
    static constexpr float origin_x = -10.0;
    static constexpr float origin_y = -10.0;
    static constexpr int image_size = 384;

    move_base_msgs::MoveBaseGoal geometry_goals[3];
    image_coordi image_goal[3];
    std::string string_goal[3] = {"거실", "주방", "화장실"};
    static std::string destination;




    
private :

    static void google_assistant_callback(const std_msgs::String::ConstPtr& msg);
    void assign_control_value()
    {
        stop_msg.linear.x = 0;
        stop_msg.linear.y = 0;
        stop_msg.angular.z = 0;

        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        goal.target_pose.pose.position.x = 1.0;
        goal.target_pose.pose.orientation.w = 1.0;

    };

    move_base_msgs::MoveBaseGoal convert_image_to_geometry(image_coordi pt);
    void set_turtlebot_goal();
    int parse_destination_to_number(std::string destination);

    







};