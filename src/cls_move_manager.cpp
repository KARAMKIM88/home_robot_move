#include "cls_move_manager.h"

int cls_move_manager::my_state = STATE_IDLE;
bool cls_move_manager::subs_flags = false;
std::string cls_move_manager::destination;

constexpr int TIME_TO_SLEEP = 7000;

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
    destination = std::string(msg->data.c_str());

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



void cls_move_manager::control_turtlebot_velocity()
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

            int goal_index = parse_destination_to_number(destination);
            velocity_ctl.publish(vel_msg[goal_index]);
            sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
           

            velocity_ctl.publish(stop_msg);

            
            subs_flags = false;
        }

        ros::spinOnce();
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

            int goal_index = parse_destination_to_number(destination);
            ROS_INFO("the goal index : %d \n", goal_index);
            if(goal_index == -1){
                ROS_INFO("Invalid location \n");
            }else{
                geometry_goals[goal_index].target_pose.header.stamp = ros::Time::now();
                ac->sendGoal(geometry_goals[goal_index]);
                my_state = STATE_GOAL;
                ac->waitForResult();

                if (ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
                {
                    my_state = STATE_IDLE;
                    ROS_INFO("Hooray, the base moved 1 meter forward");
                }
                else
                    ROS_INFO("The base failed to move forward 1 meter for some reason");


            }

            
            subs_flags = false;
        }

        ros::spinOnce();
    }
}

move_base_msgs::MoveBaseGoal cls_move_manager::convert_image_to_geometry(image_coordi pt){

    move_base_msgs::MoveBaseGoal geometry_info;

    geometry_info.target_pose.header.frame_id = "map";
    geometry_info.target_pose.pose.position.x = origin_x + resolution * pt.x;
    geometry_info.target_pose.pose.position.y = origin_y + resolution * (image_h - pt.y);
    geometry_info.target_pose.pose.orientation.w = 1.0;



    return geometry_info;


}

void cls_move_manager::set_turtlebot_goal(){

/*
    (243, 198)
    (199, 147)
    (165, 199)    

*/

    image_goal[0] = image_coordi(215, 395);
    image_goal[1] = image_coordi(159, 353);
    image_goal[2] = image_coordi(170, 232);
/*
    for(int i = 0; i<3; ++i){
        geometry_goals[i] = convert_image_to_geometry(image_goal[i]);
    }
*/



    geometry_goals[0].target_pose.header.frame_id = "map";
    geometry_goals[0].target_pose.pose.position.x = 3.04499912262;
    geometry_goals[0].target_pose.pose.position.y = -0.950000405312;
    geometry_goals[0].target_pose.pose.orientation.z = -0.707107091669;
    geometry_goals[0].target_pose.pose.orientation.w = 0.707106470704;

    geometry_goals[1].target_pose.header.frame_id = "map";
    geometry_goals[1].target_pose.pose.position.x = 0.07;
    geometry_goals[1].target_pose.pose.position.y = 0.07;
    geometry_goals[1].target_pose.pose.orientation.z = 1.0;
    geometry_goals[1].target_pose.pose.orientation.w = 0;



}

int cls_move_manager::parse_destination_to_number(std::string destination){

    int goal_index = -1;

    ssize_t pos;
    for(int i = 0; i<3; ++i){
        
        if((pos = destination.find(string_goal[i])) != std::string::npos)
        {
            goal_index = i;
            break;
        }
    }

    return goal_index;
}