#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "plumbing/msg/person.hpp"
#include "plumbing/srv/multi.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class communicate_template : public rclcpp::Node
{
	public:
		std_msgs::msg::String normal_msg;
		plumbing::msg::Person define_msg;

		rclcpp::Publisher<std_msgs::msg::String>::SharedPtr normal_pub;
		rclcpp::Subscription<std_msgs::msg::String>::SharedPtr normal_sub;
		rclcpp::Publisher<plumbing::msg::Person>::SharedPtr define_pub;
		rclcpp::Subscription<plumbing::msg::Person>::SharedPtr define_sub;
		
		rclcpp::Service<plumbing::srv::Multi>::SharedPtr server;
		rclcpp::Client<plumbing::srv::Multi>::SharedPtr client;
		
		rclcpp::TimerBase::SharedPtr timer;

		communicate_template();
		~communicate_template();
		bool connect_server();
		rclcpp::Client<plumbing::srv::Multi>::FutureAndRequestId send_requset(int32_t num1,int32_t num2);

	private:
		void timer_callback();
		void normal_callback(const std_msgs::msg::String& msg);
		void define_callback(const plumbing::msg::Person& msg);
		void server_callback(const plumbing::srv::Multi::Request::SharedPtr req,const plumbing::srv::Multi::Response::SharedPtr res);
};

#endif