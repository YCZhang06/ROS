#include "communicate/communicate.h"

communicate_template::communicate_template(ros::NodeHandle handle)
{
	handle.setParam("age",23); 
    handle.setParam("height",1.80); 
    handle.setParam("man",true); 
    handle.setParam("country","china");
}

communicate_template::~communicate_template() 
{
     
}

void communicate_template::operator_param(ros::NodeHandle nh)
{
    int res1 = nh.param("age",0); 
    int res2 = nh.param("agee",0); 
    ROS_INFO("age: %d,%d",res1,res2);
    int height;
    nh.getParam("height",height);
    ROS_INFO("height: %.2f",height);
    bool man;
    nh.getParamCached("man",man);
    ROS_INFO("has country param? %d",nh.hasParam("country"));
    std::string key;
    nh.searchParam("country",key);
    ROS_INFO("key: %s",key.c_str());
    std::vector<std::string> param_names;
    nh.getParamNames(param_names);
    for (auto &&name : param_names)
    {
        ROS_INFO("param name: %s",name.c_str());        
    }
    ROS_INFO("----------------------------");
    nh.deleteParam("country");
}