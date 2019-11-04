#ifndef SIM_MESSAGE_H
#define SIM_MESSAGE_H

#include <string>
#include "environment_object.h"
#include "clock.h"

class sim_message
{
    private:
        //things being sent to simulation:
        environment_object& requester;
        environment_object* payload;
        int x_loc;
        int y_loc;
        std::string action_requested;
        //things returned from simulation:
        std::string response;
        time_container time_info;
        bool success;
    public:
        sim_message();
        ~sim_message();
};

#endif