#include "communicate/communicate.h"

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<communicate_template>();
    if(node->connect_server())
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"connect fail");
        return 0;
    }
    auto response = node->send_requset(6,6);
    if(rclcpp::spin_until_future_complete(node,response) == rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(node->get_logger(),"result: %ld",response.get()->result);
    }
    else
    {
        RCLCPP_ERROR(node->get_logger(),"request fail");
    }
    rclcpp::shutdown();

    return 0;
}