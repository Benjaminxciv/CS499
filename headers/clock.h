/*
Name: clock.h
Purpose: Contains all header file information for clock.cpp, keeps central time for Life Simulation
Last edit: 10-22-20
Last editor: MG
*/

#ifndef CLOCK_H
#define CLOCK_H

struct time_container
{
    int time_sec = 0;
    int time_min = 0;
    int time_hour = 0;
    bool operator==(const time_container& t1, const time_container& t2)
    {
        if (t1.time_sec != t2.time_sec)
        {
            return false;
        }
        else if (t1.time_min != t2.time_min)
        {
            return false;
        }
        else if (t1.time_hour != t2.time_hour)
        {
            return false;
        }
        return true;
    }
};

class clock
{
    private:
        time_container current_time;
        
    public:
        void add_sec(int num_secs = 1);
        void add_min(int num_mins = 1);
        void add_hour(int num_hours = 1);
        time_container get_time();
};
#endif 