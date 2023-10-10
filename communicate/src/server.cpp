#include "communicate/communicate.h"

communicate_template::communicate_template() : Node("server")
{
	server = this->create_service<plumbing::srv::Multi>("multi",std::bind(&communicate_template::server_callback,this,_1,_2));
    client = this->create_client<plumbing::srv::Multi>("multi");
}

communicate_template::~communicate_template() 
{
	
}

bool communicate_template::connect_server()
{
    while(!client->wait_for_service(1s))
    {
        if(!rclcpp::ok())
        {
            return false;
        }
        RCLCPP_WARN(rclcpp::get_logger("rclcpp"),"waiting.........");
    }
    return true;
}

rclcpp::Client<plumbing::srv::Multi>::FutureAndRequestId communicate_template::send_requset(int32_t num1,int32_t num2)
{
    auto request = std::make_shared<plumbing::srv::Multi::Request>();
    request->num1 = num1;
    request->num2 = num2;
    return client->async_send_request(request);
}

void communicate_template::server_callback(const plumbing::srv::Multi::Request::SharedPtr req,const plumbing::srv::Multi::Response::SharedPtr res)
{
    res->result = req->num1 * req->num2;
}