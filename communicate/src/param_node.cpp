#include "communicate/communicate.h"

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"param_node");
    ros::NodeHandle nh;
    communicate_template node(nh);
    node.operator_param(nh);
    return 0;
}