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
    int time_pence_sec = 0;
    int time_sec = 0;
    int time_min = 0;
    int time_hor = 0;
    int time_milli_sec = 0;
};

class clock
{
    private:
        time_container current_time;
        
    public:
        void add_sec();
        void add_milli_sec();
        void add_pence_sec();
        time_container get_time();
};
#endif 