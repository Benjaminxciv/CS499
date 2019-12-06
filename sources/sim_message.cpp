/*
Name: sim_message.cpp
Purpose: Class file for sim_message. These are all the wrappers for simulation calls. This is the one communicator to the simulation.
        Thus, grid is preserved with this method. 
Last edit: 12-3-19
Last editor: AW
*/
#include "sim_message.h"

sim_message::sim_message()
{
    garbage = nullptr;
}

sim_message::~sim_message()
{

}

sim_message& sim_message::get_instance(bool reset)
{
    static sim_message sim_message_instance;
    if(reset)
    {
        sim_message_instance.time_offset_secs = -1;
        sim_message_instance.time_offset_mins = -1;
        sim_message_instance.time_offset_hours = -1;
        sim_message_instance.organism = nullptr;
        sim_message_instance.location.clear();
        sim_message_instance.search_radius = -1;
        sim_message_instance.action_requested = "";
        sim_message_instance.environment_obj_type = "";
        sim_message_instance.child_id = -1;
        sim_message_instance.parent_id = -1;
        sim_message_instance.simulation_response = "";
        sim_message_instance.multiple_responses.clear();
        sim_message_instance.energy_from_organism = -1;
        sim_message_instance.children_list.clear();
        sim_message_instance.parent = -1;
    }
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

map<point, std::string> sim_message::get_multiple_responses()
{
    return multiple_responses;
}

void sim_message::set_organism_energy(int energy)
{
    energy_from_organism = energy;
}

int sim_message::get_organism_energy()
{
    return energy_from_organism;
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

vector<point> sim_message::get_location()
{
    return location;
}

environment_object* sim_message::get_organism()
{
    return organism;
}

int sim_message::get_search_radius()
{
    return search_radius;
}

std::string sim_message::get_environment_obj_type()
{
    return environment_obj_type;
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
    location.push_back(target_loc);
    organism = organism_to_move;
    return sim->process_sim_message();
}

bool sim_message::place_organism(point target_loc, std::string organism_to_create, int p_id, int search_ring)
{
    action_requested = "place organism";
    location.push_back(target_loc);
    environment_obj_type = organism_to_create;
    search_radius = search_ring;
    parent_id = p_id;
    return sim->process_sim_message();
}

bool sim_message::replace_organism(point target_loc, std::string organism_to_create)
{
    action_requested = "replace organism";
    location.push_back(target_loc);
    environment_obj_type = organism_to_create;
    return sim->process_sim_message();
}

bool sim_message::die(environment_object* organism_to_die)
{
    action_requested = "die";
    location.push_back(organism_to_die->get_loc());
    organism = organism_to_die;
    return sim->process_sim_message();
}

bool sim_message::eat_organism(point target_loc, environment_object* eater)
{
    action_requested = "eat organism";
    organism = eater;
    location.push_back(target_loc);
    return sim->process_sim_message();
}

bool sim_message::look_at_cell(point target_loc, vector<point> multiple_locs)
{
    action_requested = "look cell";
    if(multiple_locs.size() > 0)
    {
        location = multiple_locs;
        location.insert(location.begin(), target_loc);
    }
    else
    {
        location.push_back(target_loc);
    }
    return sim->process_sim_message();
}

bool sim_message::request_reproduce(point target_loc, environment_object* organism_requesting)
{
    action_requested = "request reproduction";
    location.push_back(target_loc);
    organism = organism_requesting;
    return sim->process_sim_message();
}

void sim_message::set_garbage(environment_object* to_be_deleted)
{
    garbage = to_be_deleted;
    if(garbage != nullptr)
    {
        garbage->become_garbage();
    }
}

environment_object* sim_message::get_garbage()
{
    return garbage;
}

void sim_message::set_child_id(int id)
{
    child_id = id;
}

int sim_message::get_child_id()
{
    return child_id;
}

void sim_message::set_parent_id(int id)
{
    parent_id = id;
}

int sim_message::get_parent_id()
{
    return parent_id;
}

bool sim_message::request_child_list(int p_id)
{
    action_requested = "child list";
    parent_id = p_id;
    return sim->process_sim_message();
}

bool sim_message::request_birth(int p_id, point birth_loc)
{
    action_requested = "predator birth";
    location.push_back(birth_loc);
    parent_id = p_id;
    return sim->process_sim_message();
}

bool sim_message::request_parent_list(int c_id)
{
    action_requested = "parent list";
    child_id = c_id;
    return sim->process_sim_message();
}

void sim_message::set_child_list(vector<int> c_list)
{
    children_list = c_list;
}

void sim_message::set_baby_list(vector<int> b_list)
{
    baby_list = b_list;
}

void sim_message::set_parent(int par)
{
    parent = par;
}

vector<int> sim_message::get_child_list()
{
    return children_list;
}

vector<int> sim_message::get_baby_list()
{
    return baby_list;
}

int sim_message::get_parent()
{
    return parent;
}