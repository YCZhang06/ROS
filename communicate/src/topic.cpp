#include "communicate/communicate.h"

communicate_template::communicate_template(ros::NodeHandle handle)
{
	normal_pub = handle.advertise<std_msgs::String>("Q", 10);
	normal_sub = handle.subscribe("Q",10,&communicate_template::normal_callback,this);
	define_pub = handle.advertise<communicate::Person>("A", 10);
	define_sub = handle.subscribe("A",10,&communicate_template::define_callback,this);
	server = handle.advertiseService("multipy",&communicate_template::response_callback,this);
	client = handle.serviceClient<communicate::Multi>("multipy");
}

communicate_template::~communicate_template() 
{
     
}

void communicate_template::normal_pub_msg()
{
	normal_msg.data = "   please tell me about your information    ";
	normal_pub.publish(normal_msg);
}

void communicate_template::define_pub_msg()
{
	define_msg.name = " zyc ";
	define_msg.age = 23;
	define_msg.height = 1.80;
	define_pub.publish(define_msg);
}

void communicate_template::request()
{
	ros::service::waitForService("multipy");
	communicate::Multi m;
	m.request.num1 = 6;
    m.request.num2 = 6;
	bool flag = client.call(m);
	if (flag)
    {
        ROS_INFO("result: %ld",m.response.result);
    }
}

void communicate_template::run()
{
	ros::Rate rate(1);     
	normal_pub_msg();
	while(ros::ok())
    {
        ros::spinOnce();     
        define_pub_msg();
        rate.sleep();
    }
}

void communicate_template::normal_callback(const std_msgs::String::ConstPtr &msg)
{
	ROS_INFO("question: %s",msg->data.c_str());
}

void communicate_template::define_callback(const communicate::Person::ConstPtr &msg)
{
	ROS_INFO("I know, you are: %s. age %d. height %.2f. ",msg->name.c_str(),msg->age,msg->height);
}

bool communicate_template::response_callback(communicate::Multi::Request &req,communicate::Multi::Response &res)
{
	int num1 = req.num1;
    int num2 = req.num2;
	res.result = num1 * num2;
	return true;
}