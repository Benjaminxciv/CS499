/*Name: clock.cpp
Purpose: Keep time for Life Simulation, provides central clock for all objects to time their actions.
Last edit: 10-22-20
Last editor: MG*/

#include "clock.h"

//TODO: Add method comment block
void clock::add_sec(int num_secs)
{
    for(int i = 0; i < num_secs; i++)
    {
        this->current_time.time_sec++;

        if (this->current_time.time_sec >= 60)
        {
            this->current_time.time_sec = 0;
            this->current_time.time_min++;

            if (this->current_time.time_min >= 60)
            {
                this->current_time.time_min = 0; 
                this->current_time.time_hor++;
            }
        }
    }
}

void clock::add_pence_sec()
{
    this->current_time.time_pence_sec++;

    if(this->current_time.time_pence_sec >= 50)
    {
        this->add_sec();
        this->current_time.time_pence_sec = 0;
    }
}

void clock::add_milli_sec()
{
    this->current_time.time_milli_sec++;

    if (this->current_time.time_milli_sec >= 1000)
    {      
        this->add_sec();
    }           
}

time_container clock::get_time()
{
    return this->current_time;
}



