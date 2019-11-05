#ifndef SIM_MESSAGE_H
#define SIM_MESSAGE_H

#include <string>
#include "environment_object.h"
#include "clock.h"

class sim_message
{
    private:
        //things being sent to simulation:
        environment_object* organism;
        int x_loc;
        int y_loc;
        std::string action_requested;
        //things returned from simulation:
        std::string simulation_response;
        clock* time_info;
        sim_message();
        ~sim_message();
    public:
        static sim_message& get_instance();
        bool request_action(std::string, int, int);
        bool request_action(std::string, int, int, environment_object*);
        void set_simulation_response(std::string);
        std::string get_simulation_response();
        void set_time_info(clock*);
        clock* get_current_time();
        clock* get_future_time(int);
};


#endif