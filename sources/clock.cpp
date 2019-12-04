/*Name: clock.cpp
Purpose: Defines the timesteps for the simulation clock. Allows us to compare times directly. 
Last edit: 12-2-19
Last editor: MG*/

#include "clock.h"
using namespace sim_ns;


void clock::add_sec(int num_secs)
{
    for(int i = 0; i < num_secs; i++)
    {
        this->current_time.time_sec++;

        if (this->current_time.time_sec >= 60)
        {
            this->current_time.time_sec = 0;
            this->add_min();
        }
    }
}

void clock::add_min(int num_mins)
{
    for(int i = 0; i < num_mins; i++)
    {
        this->current_time.time_min++;

        if(this->current_time.time_min >= 60)
        {
           this->current_time.time_min = 0;
           this->add_hour();
        }
    }
}

void clock::add_hour(int num_hours)
{
    for(int i = 0; i < num_hours; i++)
    {
        this->current_time.time_hour++;
    }         
}

time_container clock::get_time()
{
    return this->current_time;
}



