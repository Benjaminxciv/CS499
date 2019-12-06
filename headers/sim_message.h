/*
Name: sim_message.h
Purpose: Header file for sim_message. These are all the wrappers for simulation calls.  
Last edit: 12-3-19
Last editor: AW
*/

#ifndef SIM_MESSAGE_H
#define SIM_MESSAGE_H

#include <string>
#include <map>
#include "environment_object.h"
#include "clock.h"
#include "simulation.h"

class simulation;

class sim_message
{
    private:
        //things being sent to simulation:
        environment_object* organism;
        int time_offset_secs;
        int time_offset_mins;
        int time_offset_hours;
        vector<point> location;
        int search_radius;
        std::string action_requested;
        std::string environment_obj_type;
        int child_id;
        int parent_id;
        //things returned from simulation:
        std::string simulation_response;
        map<point, std::string> multiple_responses;
        int energy_from_organism;
        time_container time_info;
        simulation* sim;
        environment_object* garbage;
        vector<int> children_list;
        vector<int> baby_list;
        int parent;
        sim_message();
        ~sim_message();
        friend class simulation;
    public:
        static sim_message& get_instance(bool reset = true);
        void set_sim(simulation*);
        bool process_message();
        std::string get_action_requested();
        void set_simulation_response(std::string);
        std::string get_simulation_response();
        map<point, std::string> get_multiple_responses();
        void set_organism_energy(int);
        int get_organism_energy();
        int get_time_offset_secs();
        int get_time_offset_mins();
        int get_time_offset_hours();
        vector<point> get_location();
        environment_object* get_organism();
        int get_search_radius();
        std::string get_environment_obj_type();
        void set_time_info(time_container);
        time_container get_time_info();
        bool get_current_time();
        bool get_future_time(int future_secs = 0, int future_mins = 0, int future_hours = 0);
        bool move_organism(point, environment_object*);
        bool place_organism(point, std::string, int, int search_ring = 1);
        bool replace_organism(point, std::string);
        bool die(environment_object*);
        bool eat_organism(point, environment_object* eater = nullptr);
        bool look_at_cell(point, vector<point> = vector<point>());
        bool request_reproduce(point, environment_object*);
        void set_garbage(environment_object*);
        void set_child_id(int id);
        int get_child_id();
        void set_parent_id(int id);
        int get_parent_id();
        bool request_child_list(int);
        bool request_birth(int, point);
        bool request_parent_list(int);
        void set_child_list(vector<int>);
        void set_baby_list(vector<int>);
        void set_parent(int);
        vector<int> get_child_list();
        vector<int> get_baby_list();
        int get_parent();
        environment_object* get_garbage();
};


#endif