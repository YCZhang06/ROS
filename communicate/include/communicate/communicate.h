#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "plumbing/msg/person.hpp"

using namespace std::chrono_literals;

class communicate_template : public rclcpp::Node
{
	public:
		std_msgs::msg::String normal_msg;
		plumbing::msg::Person define_msg;

		rclcpp::Publisher<std_msgs::msg::String>::SharedPtr normal_pub;
		rclcpp::Subscription<std_msgs::msg::String>::SharedPtr normal_sub;
		rclcpp::Publisher<plumbing::msg::Person>::SharedPtr define_pub;
		rclcpp::Subscription<plumbing::msg::Person>::SharedPtr define_sub;
		rclcpp::TimerBase::SharedPtr timer;

		communicate_template();
		~communicate_template();

	private:
		void timer_callback();
		void normal_callback(const std_msgs::msg::String& msg);
		void define_callback(const plumbing::msg::Person& msg);
};

#endif