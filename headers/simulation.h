/*
Name: simulation.h
Purpose: Contains all header file information for simulation.cpp, controls flow of Life Simulation
Last edit: 
Last editor: 
*/


#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include "grid.h"
#include "boulder.h"
#include "LifeSimDataParser.h"
#include "plant.h"
#include "predator.h"
#include "grazer.h"
#include "clock.h"
#include "sim_message.h"

enum tick_speeds {x1 = 1, x10 = 10, x50 = 50, x100 = 100};

class simulation
{
    private:
        int tick_speed;
        clock* simulation_clock;
        grid* sim_grid;
    public:
        simulation();
        ~simulation();
        void run_sim();
        void set_tick_speed(int);
        void increase_tick_speed();
        void increment_simulation_clock();
        time_container get_simulation_time();
        bool process_sim_message();
};

#endif