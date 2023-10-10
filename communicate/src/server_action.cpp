#include "communicate/communicate.h"

communicate_template::communicate_template() : Node("server")
{
	server = this->create_service<plumbing::srv::Multi>("multi",std::bind(&communicate_template::server_callback,this,_1,_2));
    client = this->create_client<plumbing::srv::Multi>("multi");
    server_action = rclcpp_action::create_server<plumbing::action::Progress>(this, "total",std::bind(&communicate_template::goal_callback,this,_1,_2),std::bind(&communicate_template::cancel_callback,this,_1),std::bind(&communicate_template::accept_callback,this,_1));
    client_action = rclcpp_action::create_client<plumbing::action::Progress>(this,"total");
}

communicate_template::~communicate_template() 
{
	
}

bool communicate_template::connect_server()
{
    while(!client->wait_for_service(1s))
    {
        if(!rclcpp::ok())
        {
            return false;
        }
        RCLCPP_WARN(rclcpp::get_logger("rclcpp"),"waiting.........");
    }
    return true;
}

rclcpp::Client<plumbing::srv::Multi>::FutureAndRequestId communicate_template::send_requset(int32_t num1,int32_t num2)
{
    auto request = std::make_shared<plumbing::srv::Multi::Request>();
    request->num1 = num1;
    request->num2 = num2;
    return client->async_send_request(request);
}

rclcpp_action::GoalResponse communicate_template::goal_callback(const rclcpp_action::GoalUUID& uuid,std::shared_ptr<const plumbing::action::Progress::Goal> goal)
{
    (void)uuid;
    (void)goal;
    RCLCPP_INFO(this->get_logger(),"input num receive");
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse communicate_template::cancel_callback(std::shared_ptr<rclcpp_action::ServerGoalHandle<plumbing::action::Progress>> goalhandle)
{
    (void)goalhandle;
    RCLCPP_INFO(this->get_logger(),"cancel !!!!!!");
    return rclcpp_action::CancelResponse::ACCEPT;
}

void communicate_template::execute(std::shared_ptr<rclcpp_action::ServerGoalHandle<plumbing::action::Progress>> goalhandle)
{
    int num = goalhandle->get_goal()->num;
    int sum = 0;
    auto feedback = std::make_shared<plumbing::action::Progress::Feedback>();
    rclcpp::Rate rate(1.0);
    auto result = std::make_shared<plumbing::action::Progress::Result>();
    for(int i = 1; i <= num; i++)
    {
        sum += i;
        double progress = i / (double)num;
        feedback->progress = progress;
        goalhandle->publish_feedback(feedback);
        RCLCPP_INFO(this->get_logger(),"progress: %.2f", progress);
        if(goalhandle->is_canceling())
        {
            result->sum = sum;
            goalhandle->canceled(result);
            RCLCPP_INFO(this->get_logger(),"stop, result: %d", sum);
            return;
        }
        rate.sleep();
    }
    if(rclcpp::ok())
    {
        result->sum = sum;
        goalhandle->succeed(result);
        RCLCPP_INFO(this->get_logger(),"finish, result: %d", sum);
    }
}

void communicate_template::accept_callback(std::shared_ptr<rclcpp_action::ServerGoalHandle<plumbing::action::Progress>> goalhandle)
{
    std::thread(std::bind(&communicate_template::execute,this,goalhandle)).detach();
}

void communicate_template::send_request(int num)
{
    if(!client_action->wait_for_action_server(5s))
    {
        RCLCPP_ERROR(this->get_logger(),"connect server fail");
        return;
    }
    auto goal = plumbing::action::Progress::Goal();
    goal.num = num;
    auto options = rclcpp_action::Client<plumbing::action::Progress>::SendGoalOptions();
    options.feedback_callback = std::bind(&communicate_template::feedback_callback,this,_1,_2);
    options.goal_response_callback = std::bind(&communicate_template::goal_response_callback,this,_1);
    options.result_callback = std::bind(&communicate_template::result_callback,this,_1);
    auto future = client_action->async_send_goal(goal,options);
}

void communicate_template::server_callback(const plumbing::srv::Multi::Request::SharedPtr req,const plumbing::srv::Multi::Response::SharedPtr res)
{
    res->result = req->num1 * req->num2;
}

void communicate_template::feedback_callback(rclcpp_action::ClientGoalHandle<plumbing::action::Progress>::SharedPtr goal_handle,const std::shared_ptr<const plumbing::action::Progress::Feedback> feedback)
{
    (void)goal_handle;
    double progress = feedback->progress;
    RCLCPP_INFO(this->get_logger(),"now progress: %d%%",(int)(progress*100));
}

void communicate_template::goal_response_callback(rclcpp_action::ClientGoalHandle<plumbing::action::Progress>::SharedPtr goal_handle)
{
    if(!goal_handle)
    {
        RCLCPP_ERROR(this->get_logger(),"request be refused");
    }
    else
    {
        RCLCPP_INFO(this->get_logger(),"request be allowed");
    }
}

void communicate_template::result_callback(const rclcpp_action::ClientGoalHandle<plumbing::action::Progress>::WrappedResult& result)
{
    if(result.code == rclcpp_action::ResultCode::SUCCEEDED)
    {
        RCLCPP_INFO(this->get_logger(),"response: %ld",result.result->sum);
    }
    else if(result.code == rclcpp_action::ResultCode::ABORTED || result.code == rclcpp_action::ResultCode::CANCELED)
    {
        RCLCPP_WARN(this->get_logger(),"request be interupt or cancel");
    }
    else
    {
        RCLCPP_ERROR(this->get_logger(),"request counter unknow question");
    }
}