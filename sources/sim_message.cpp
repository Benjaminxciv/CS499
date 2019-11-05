#include "sim_message.h"

sim_message::sim_message()
{

}

sim_message::~sim_message()
{

}

sim_message& sim_message::get_instance()
{
    static sim_message sim_message_instance;
    return sim_message_instance;
}

void sim_message::set_sim(simulation* sim)
{
    this->sim = sim;
}

bool sim_message::process_message()
{
    return this->sim->process_sim_message();
}

void sim_message::request_action(std::string action_requested, int x_loc, int y_loc)
{
    
}

void sim_message::request_action(std::string action_request, int x_loc, int y_loc, environment_object* organism)
{
    
}

std::string sim_message::get_action_requested()
{
    return this->action_requested;
}

void sim_message::set_simulation_response(std::string simulation_response)
{
    this->simulation_response = simulation_response;
}

std::string sim_message::get_simulation_response()
{
    return this->simulation_response;
}

int sim_message::get_time_offset()
{
    return this->time_offset;
}

void sim_message::set_time_info(time_container* time_info)
{
    this->time_info = time_info;
}

time_container* sim_message::get_time_info()
{
    return this->time_info;
}

void sim_message::get_current_time()
{
    this->action_requested = "get curr_time";
    this->time_offset = 0;
}

void sim_message::get_future_time(int future_time)
{
    this->action_requested = "get future_time";
    this->time_offset = future_time;
}