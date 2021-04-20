#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/String.h>
#include <move_base_msgs/MoveBaseResult.h>


//ros acml_pose subscribe status check
// ros  

enum State{
	STATE_IDLE,
	STATE_GOAL,
	STATE_MONITORING //future work
};

State my_state;

//should add state change idle -> move


void google_assistant_callback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("I heard : [%s]", msg->data.c_str());

	if(my_state == STATE_MONITORING){
		//send goal cancel
		my_state = STATE_IDLE; 
	}else if(my_state == STATE_IDLE){

	}

}


void move_base_callback(&msg){
	ROS_INFO("move base callback %s", msg.status.text);

	if(my_state == STATE_GOAL){
		if(msg.status.status == 3){
			ROS_INFO("change")
			my_state = STATE_IDLE;
		}
	}
}



int main(int argc, char** argv){

	ros::init(argc, argv, "home_robot_navi");

	ros::NodeHandle nh;
	ros::Publisher ros_move_pub = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 10);
	
	ros::Subscriber ga_state_manager = nh.subscribe("GA", 10, google_assistant_callback);
	ros::Subscriber robot_state_manager = nh.subscribe("/move_base/result", 10, move_base_callback);

	geometry_msgs::PoseStamped goal;

	ros::Rate loop_rate(1);




	goal.header.frame_id = "map";
	//goal.header.stamp = ros::Time::now();
	goal.pose.position.x = -0.2;
	goal.pose.position.y = =0.8;
	goal.pose.orientation.w = 0.0;
	

	my_state = STATE_IDLE;
	
	
	ROS_INFO("publish goal");

	while(ros::ok()){

		if(my_state == STATE_GOAL){

			ros_move_pub.publish(goal);
		}

		if(my_state == STATE_GOAL && msg == "finish"){
			my_state = STATE_IDLE;
		}

		if(my_state == STATE_IDLE){
			ros_move_pub.publish()
		}

		ros::spinOnce();
	}


	return 0;

}






