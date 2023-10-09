#include "communicate/communicate.h"

communicate_template::communicate_template(ros::NodeHandle handle)
{
	server = handle.advertiseService("multipy",&communicate_template::response_callback,this);
	client = handle.serviceClient<communicate::Multi>("multipy");
}

communicate_template::~communicate_template() 
{
     
}

void communicate_template::request()
{
	ros::service::waitForService("multipy");
	communicate::Multi m;
	m.request.num1 = 6;
    m.request.num2 = 6;
	bool flag = client.call(m);
	if (flag)
    {
        ROS_INFO("result: %ld",m.response.result);
    }
}

bool communicate_template::response_callback(communicate::Multi::Request &req,communicate::Multi::Response &res)
{
	int num1 = req.num1;
    int num2 = req.num2;
	res.result = num1 * num2;
	return true;
}