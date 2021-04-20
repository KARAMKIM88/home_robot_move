#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>


int main(int argc, char** argv){

	ros::init(argc, argv, "home_robot_navi");

	ros::NodeHandle nh;
	ros::Publisher ros_move_pub = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 10);
	ros::Subscriber ros_state_manage = 

	geometry_msgs::PoseStamped goal;

	ros::Rate loop_rate(10);


	goal.header.frame_id = "map";
	goal.header.stamp = ros::Time::now();
	goal.pose.position.x = -0.4;
	goal.pose.position.y = -0.4;
	

	ros_move_pub.publish(goal);
	
	ros::Duration(5).sleep();
	
	ROS_INFO("publish goal");

	while(ros::ok()){

		ros::spinOnce();
	}


	return 0;

}






