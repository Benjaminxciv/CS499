/*
Name: clock.h
Purpose: Contains all header file information for clock.cpp, keeps central time for Life Simulation.
Last edit: 12-3-19
Last editor: MG
*/

#ifndef CLOCK_H
#define CLOCK_H

struct time_container
{
    int time_sec = 0;
    int time_min = 0;
    int time_hour = 0;
    bool operator==(const time_container& t1)
    {
        return (time_sec == t1.time_sec && time_min == t1.time_min && time_hour == t1.time_hour);
    }
    bool operator>(const time_container& t1)
    {
        if(time_hour > t1.time_hour)
        {
            return true;
        }
        else if(time_hour == t1.time_hour)
        {
            if(time_min > t1.time_min)
            {
                return true;
            }
            else if(time_min == t1.time_min)
            {
                if(time_sec > t1.time_sec)
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool operator>=(const time_container& t1)
    {
        return (*this > t1 || *this == t1);
    }
};

namespace sim_ns
{
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
}
#endif 