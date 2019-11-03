#ifndef SIM_MESSAGE_H
#define SIM_MESSAGE_H

#include <string>
#include "environment_object.h"

class sim_message
{
    private:
        environment_object& sender;
        environment_object& target;
        string action;
    public:
        sim_message();
        ~sim_message();
};

#endif