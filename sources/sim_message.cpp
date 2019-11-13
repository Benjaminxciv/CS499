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

void sim_message::set_sim(simulation* sim_ref)
{
    sim = sim_ref;
}

bool sim_message::process_message()
{
    return sim->process_sim_message();
}

std::string sim_message::get_action_requested()
{
    return action_requested;
}

void sim_message::set_simulation_response(std::string sim_response)
{
    simulation_response = sim_response;
}

std::string sim_message::get_simulation_response()
{
    return simulation_response;
}

int sim_message::get_time_offset_secs()
{
    return time_offset_secs;
}

int sim_message::get_time_offset_mins()
{
    return time_offset_mins;
}

int sim_message::get_time_offset_hours()
{
    return time_offset_hours;
}

point sim_message::get_location()
{
    return location;
}

environment_object* sim_message::get_organism()
{
    return organism;
}

void sim_message::set_time_info(time_container new_time_info)
{
    time_info = new_time_info;
}

time_container sim_message::get_time_info()
{
    return time_info;
}

bool sim_message::get_current_time()
{
    action_requested = "get curr_time";
    time_offset_secs = 0;
    time_offset_mins = 0;
    time_offset_hours = 0;
    return sim->process_sim_message();
}

bool sim_message::get_future_time(int future_secs, int future_mins, int future_hours)
{
    action_requested = "get future_time";
    time_offset_secs = future_secs;
    time_offset_mins = future_mins;
    time_offset_hours = future_hours;
    return sim->process_sim_message();
}

bool sim_message::move_organism(point target_loc, environment_object* organism_to_move)
{
    action_requested = "move organism";
    location = target_loc;
    organism = organism_to_move;
    return sim->process_sim_message();

}

bool sim_message::place_organism(point target_loc, environment_object* organism_to_move)
{
    action_requested = "place organism";
    location = target_loc;
    organism = organism_to_move;
    return sim->process_sim_message();
}

bool sim_message::eat_organism(point target_loc, environment_object* organism_to_move)
{
    action_requested = "eat organism";
    location = target_loc;
    organism = organism_to_move;
    return sim->process_sim_message();
}

bool sim_message::look_at_cell(point target_loc)
{
    action_requested = "look cell";
    location = target_loc;
    return sim->process_sim_message();
}

bool sim_message::request_reproduce(point target_loc, environment_object* organism_to_move)
{
    action_requested = "eat organism";
    location = target_loc;
    organism = organism_to_move;
    return sim->process_sim_message();
}