#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/String.h>


//ros acml_pose subscribe status check
// ros  

enum State{
	STATE_IDLE,
	STATE_GOAL,
	STATE_MONITORING
};

State my_state;



void google_assistant_callback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("I heard : [%s]", msg->data.c_str());

	if(my_state == STATE_MONITORING){
		//send goal cancel
		my_state = STATE_IDLE; 
	}else if(my_state == STATE_IDLE){

	}

}



int main(int argc, char** argv){

	ros::init(argc, argv, "home_robot_navi");

	ros::NodeHandle nh;
	ros::Publisher ros_move_pub = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 10);
	ros::Subscriber ros_state_manage = nh.subscribe("GA", 10, google_assistant_callback);

	geometry_msgs::PoseStamped goal;

	ros::Rate loop_rate(1);

	ros::Time


	goal.header.frame_id = "map";
	//goal.header.stamp = ros::Time::now();
	goal.pose.position.x = -1;
	goal.pose.position.y = -1;
	

	my_state = STATE_IDLE;
	
	
	ROS_INFO("publish goal");

	while(ros::ok()){

		if(my_state == STATE_GOAL){

			ros_move_pub.publish(goal);
		}

		if(my_state == STATE_GOAL && msg == "finish"){
			my_state = STATE_IDLE;
		}

		ros::spinOnce();
	}


	return 0;

}






