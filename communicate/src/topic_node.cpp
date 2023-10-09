#include "communicate/communicate.h"

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"topic_node");
    ros::NodeHandle nh;
    communicate_template node(nh);
    node.run();
    return 0;
}