#include "communicate/communicate.h"

int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<communicate_template>();
    node->add();
    node->search();
    node->revise();
    node->del();
    node->get();
    node->update();
    node->get();
    rclcpp::shutdown();
    
    return 0;
}