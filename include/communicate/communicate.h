#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include "ros/ros.h"
#include <std_msgs/String.h>


class communicate
{
	public:
		std_msgs::String pub_msg;

		ros::Publisher pub; 
		ros::Subscriber sub;

		communicate(ros::NodeHandle nh);
		~communicate();
		void pub_msg();
		void run();

	private:
		void callback(const std_msgs::String::ConstPtr &msg);  
}
