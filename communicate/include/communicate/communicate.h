#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include "ros/ros.h"
#include <std_msgs/String.h>
#include "communicate/Person.h"
#include "communicate/Multi.h"

class communicate_template
{
	public:
		std_msgs::String normal_msg;
		communicate::Person define_msg;

		ros::Publisher normal_pub; 
		ros::Publisher define_pub; 
		ros::Subscriber normal_sub;
		ros::Subscriber define_sub;

		ros::ServiceServer server;
		ros::ServiceClient client;

		communicate_template(ros::NodeHandle nh);
		~communicate_template();
		void normal_pub_msg();
		void define_pub_msg();
		void request();
		void run();

	private:
		void normal_callback(const std_msgs::String::ConstPtr &msg);  
		void define_callback(const communicate::Person::ConstPtr &msg);  
		bool response_callback(communicate::Multi::Request &req, communicate::Multi::Response &res);
};

#endif