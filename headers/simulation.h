/*
Name: simulation.h
Purpose: Contains all header file information for simulation.cpp, controls flow of Life Simulation
Last edit: 
Last editor: 
*/


#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "grid.h"
#include "boulder.h"
#include "LifeSimDataParser.h"
#include "plant.h"
#include "clock.h"
#include "sim_message.h"
#include "time.h"

enum tick_speeds {x1 = 1, x10 = 10, x50 = 50, x100 = 100};

class plant;
class leaf;
class grazer;
class predator;
class seed;

class simulation
{
    private:
        int tick_speed;
        sim_ns::clock* simulation_clock;
        int world_height;
        int world_width;
        grid* sim_grid;
        point find_empty_cell(point, int search_radius = 1);
        std::vector<environment_object*> created_objects;
    public:
        simulation();
        ~simulation();
        int get_world_height();
        int get_world_width();
        void init_sim();
        void run_sim();
        void set_tick_speed(int);
        int get_tick_speed();
        void increase_tick_speed();
        void iterate_cells();
        std::vector<environment_object*> get_created_objects();
        boulder* create_boulder(point, int, int);
        boulder_piece *create_boulder_piece(point, int);
        plant* create_plant(point, int);
        leaf* create_leaf(point);
        seed* create_seed(point);
        grazer* create_grazer(point, int);
        predator* create_predator(point, int, char*, bool);
        void increment_simulation_clock();
        time_container get_simulation_time();
        bool process_sim_message();
};
#endif