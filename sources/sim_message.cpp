#include "sim_message.h"

sim_message::sim_message()
{
}

sim_message::~sim_message()
{
}

sim_message& sim_message::get_instance()
{
    static sim_message sim_message_instance();
    return sim_message_instance;
}

bool sim_message::request_action(std::string action_requested, int x_loc, int y_loc)
{

}

bool sim_message::request_action(std::string action_request, int x_loc, int y_loc, environment_object* organism)
{

}

void sim_message::set_simulation_response(std::string simulation_response)
{
    this->simulation_response = simulation_response;
}

std::string sim_message::get_simulation_response()
{
    return this->simulation_response;
}

void sim_message::set_time_info(clock time_info)
{
    this->time_info = time_info;
}

clock sim_message::get_current_time()
{
    this->action_requested = "get curr_time";

}

clock sim_message::get_future_time(int future_time)
{
    this->get_current_time();
    this->time_info->add_sec(future_time);
    return this->time_info;
}