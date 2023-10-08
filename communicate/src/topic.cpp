#include "communicate/communicate.h"

communicate::communicate(ros::NodeHandle handle)
{
	pub = handle.advertise<std_msgs::String>("name", 10);
	sub = handle.subscribe("name",10,&communicate::callback,this);
}

communicate::~communicate() 
{
     
}

void communicate::pub_msg()
{
	pub_msgs.data = "my name is zyc ---";
	pub.publish(pub_msgs);
}

void communicate::run()
{
	ros::Rate rate(50);     
	while(ros::ok())
    {
        ros::spinOnce();     
        pub_msg();
        rate.sleep();
    }
}

void communicate::callback(const std_msgs::String::ConstPtr &msg)
{
	ROS_INFO("I know, you are: %s",msg->data.c_str());
}