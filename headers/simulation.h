#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include "grid.h"
#include "boulder.h"
#include "LifeSimDataParser.h"

class simulation
{
    private:
        int tick_speed;
    public:
        simulation();
        ~simulation();
        void run_sim();
        void set_tick_speed(int);
};

#endif