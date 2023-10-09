#include "communicate/communicate.h"

int main(int argc, char const *argv[])
{
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<communicate_template>());
  rclcpp::shutdown();

  return 0;
}