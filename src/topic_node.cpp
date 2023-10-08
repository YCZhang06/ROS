#include "communicate/communicate.h"

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "communicate_node");
  ros::NodeHandle nh;
  communicate node(nh);
  node.run();
  return 0;
}