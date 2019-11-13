#ifndef SIM_MESSAGE_H
#define SIM_MESSAGE_H

#include <string>
#include "environment_object.h"
#include "clock.h"
#include "simulation.h"

class sim_message
{
    private:
        //things being sent to simulation:
        environment_object* organism;
        int time_offset_secs;
        int time_offset_mins;
        int time_offset_hours;
        point location;
        std::string action_requested;
        //things returned from simulation:
        std::string simulation_response;
        time_container time_info;
        simulation* sim;
        sim_message();
        ~sim_message();
    public:
        static sim_message& get_instance();
        void set_sim(simulation*);
        bool process_message();
        std::string get_action_requested();
        void set_simulation_response(std::string);
        std::string get_simulation_response();
        int get_time_offset_secs();
        int get_time_offset_mins();
        int get_time_offset_hours();
        point get_location();
        environment_object* get_organism();
        void set_time_info(time_container);
        time_container get_time_info();
        bool get_current_time();
        bool get_future_time(int future_secs = 0, int future_mins = 0, int future_hours = 0);
        bool move_organism(point, environment_object*);
        bool place_organism(point, environment_object*);
        bool eat_organism(point, environment_object*);
        bool look_at_cell(point);
        bool request_reproduce(point, environment_object*);
};


#endif