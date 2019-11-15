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
#include <vector>
#include "plant.h"
#include "predator.h"
#include "grazer.h"
#include "clock.h"
#include "sim_message.h"
#include "time.h"

enum tick_speeds {x1 = 1, x10 = 10, x50 = 50, x100 = 100};

class simulation
{
    private:
        int tick_speed;
        sim_ns::clock* simulation_clock;
        int world_height;
        int world_width;
        grid* sim_grid;
    public:
        simulation();
        ~simulation();
        int get_world_height();
        int get_world_width();
        void init_sim();
        void run_sim();
        void set_tick_speed(int);
        void increase_tick_speed();
        std::vector<environment_object*> iterate_cells();
        void increment_simulation_clock();
        time_container get_simulation_time();
        bool process_sim_message();
};

#endif