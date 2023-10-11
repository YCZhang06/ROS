#include "communicate/communicate.h"

communicate_template::communicate_template() : Node("param", rclcpp::NodeOptions().allow_undeclared_parameters(true))
{
	client_param = std::make_shared<rclcpp::SyncParametersClient>(this,"param");
}

communicate_template::~communicate_template() 
{
	
}

void communicate_template::add()
{
    RCLCPP_INFO(this->get_logger(),"-------------------------------add-------------------");
    this->declare_parameter("name", "zyc");
    this->declare_parameter("age", 23);
    this->declare_parameter("height", 180.0);
    this->set_parameter(rclcpp::Parameter("sex","man"));
}

void communicate_template::search()
{
    RCLCPP_INFO(this->get_logger(),"-------------------------------search-------------------");
    rclcpp::Parameter p1 = this->get_parameter("name");
    RCLCPP_INFO(this->get_logger(),"key: %s, value: %s",p1.get_name().c_str(),p1.as_string().c_str());
    auto p2 = this->get_parameters({"age","height"});
    for (auto &&param : p2)
    {
    RCLCPP_INFO(this->get_logger(),"key: %s, value: %s",param.get_name().c_str(),param.value_to_string().c_str());
    }
    RCLCPP_INFO(this->get_logger(),"has sex param? 1-yese 0-no: %d",this->has_parameter("sex"));
}

void communicate_template::revise()
{
    RCLCPP_INFO(this->get_logger(),"-------------------------------revise-------------------");
    this->set_parameter(rclcpp::Parameter("name","lrl"));
    RCLCPP_INFO(this->get_logger(),"key: %s, value: %s",this->get_parameter("name").get_name().c_str(),this->get_parameter("name").as_string().c_str());
}

void communicate_template::del()
{
    RCLCPP_INFO(this->get_logger(),"-------------------------------del-------------------");
    this->undeclare_parameter("sex");
    RCLCPP_INFO(this->get_logger(),"has sex param? 1-yese 0-no: %d",this->has_parameter("sex"));
}

void communicate_template::get()
{
    RCLCPP_INFO(this->get_logger(),"--------------------get-----------------");
    auto name = client_param->get_parameter<std::string>("name");
    auto height = client_param->get_parameter<double>("height");
    RCLCPP_INFO(this->get_logger(),"name: %s, width: %.2f",name.c_str(),height);
    auto params = client_param->get_parameters({"height","age"});
    for (auto &&param : params)
    {
    RCLCPP_INFO(this->get_logger(),"key: %s, value: %s",param.get_name().c_str(),param.value_to_string().c_str());
    }
    RCLCPP_INFO(this->get_logger(),"has sex param? 1-yese 0-no: %d",this->has_parameter("sex"));
}

void communicate_template::update()
{
    RCLCPP_INFO(this->get_logger(),"--------------------update-----------------");
    client_param->set_parameters({rclcpp::Parameter("name","xxx"),rclcpp::Parameter("age",0),rclcpp::Parameter("?","??")});
}