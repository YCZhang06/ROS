#include "communicate/communicate.h"

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"server_node");
    ros::NodeHandle nh;
    communicate_template node(nh);
    ros::spin();
    return 0;
}