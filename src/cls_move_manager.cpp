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
    destination = msg->data;

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

            int goal_index = parse_destination_to_number(destination);
            ac->sendGoal(gemometry_goal[goal_index]);
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

geometry_msgs::Twist cls_move_manager::convert_image_to_geometry(img_coordi pt){

    geometry_msgs::Twist geometry_info;

    geometry_info.target_pose.header.frame_id = "map";
    geometry_info.target_pose.pose.position.x = origin_x + resolution * pt.x;
    geometry_info.target_pose.pose.position.y = origin_y + resolution * (image_size - pt.y);


    return geometry_info;


}

void cls_move_manager::set_turtlebot_goal(){

/*
    (243, 198)
    (199, 147)
    (165, 199)    

*/

    image_goal[0] = image_coordi(243, 198);
    image_goal[1] = image_coordi(199, 147);
    image_goal[2] = image_coordi(165, 199);

    for(i = 0; i<3; ++i){
        geometry_goal[i] = convert_image_to_geometry(image_goal[i]);
    }

}

int cls_move_manager::parse_destination_to_number(std::string destination){

    int goal_index = -1;

    for(int i = 0; i<3; ++i){
        int equal = string_goal[i].compare(destination);
        if(equal == 0)
        {
            goal_index = i;
            break;
        }
    }

    return goal_index;
}