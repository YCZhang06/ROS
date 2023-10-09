#include "communicate/communicate.h"

communicate_template::communicate_template() : Node("topic")
{
	normal_pub = this->create_publisher<std_msgs::msg::String>("Q",10);
	normal_sub = this->create_subscription<std_msgs::msg::String>("Q",10,std::bind(&communicate_template::normal_callback,this,std::placeholders::_1));
	define_pub = this->create_publisher<plumbing::msg::Person>("A",10);
	define_sub = this->create_subscription<plumbing::msg::Person>("A",10,std::bind(&communicate_template::define_callback,this,std::placeholders::_1));
	timer = this->create_wall_timer(1s,std::bind(&communicate_template::timer_callback,this));
}

communicate_template::~communicate_template() 
{
	
}

void communicate_template::timer_callback()
{
	normal_msg.data = "   please tell me about your information    ";
    normal_pub->publish(normal_msg);
	define_msg.age = 23;
    define_msg.height = 180.0;
    define_msg.name = "zyc";
    define_pub->publish(define_msg);
}

void communicate_template::normal_callback(const std_msgs::msg::String& msg)
{
	RCLCPP_INFO(this->get_logger(),"question: %s",msg.data.c_str());
}

void communicate_template::define_callback(const plumbing::msg::Person& msg)
{
	RCLCPP_INFO(this->get_logger(),"I know, you are: age:  %s. age %d. height %.2f.",msg.name.c_str(),msg.age,msg.height);
}