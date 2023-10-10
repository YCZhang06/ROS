#include "communicate/communicate.h"

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<communicate_template>();
    node->send_request(10);
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}