/*
Name: simulation.h
Purpose: Contains all header file information for simulation.cpp, controls flow of Life Simulation.
Last edit: 12-3-19
Last editor: AW
*/


#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "grid.h"
#include "boulder.h"
#include "LifeSimDataParser.h"
#include "plant.h"
#include "clock.h"
#include "sim_message.h"
#include "time.h"

enum tick_speeds {x0 = 0, x1 = 1, x10 = 10, x50 = 50, x100 = 100, x1000 = 1000};

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
        vector<environment_object*> created_objects;
        map<int, vector<int>> parent_children;
        map<int, int> children_parent;
        map<int, vector<predator*>> unborn_babies;
    public:
        simulation();
        ~simulation();
        int get_world_height();
        int get_world_width();
        void init_sim();
        void run_sim();
        void set_tick_speed(int);
        int get_tick_speed();
        void iterate_cells();
        vector<environment_object*> get_created_objects();
        bool create_boulder(point, int, int);
        bool create_boulder_piece(point, int);
        bool create_plant(point, int);
        bool create_leaf(point, int, int);
        bool create_seed(point);
        bool create_grazer(point, int, int p_id = -1);
        bool create_predator(point, int, char*, bool, int parent = -1);
        bool homo_recessive_fight(bool, bool, bool);
        bool homo_dominant_fight(bool, bool, bool);
        bool hetero_fight(bool, bool, bool);
        void increment_simulation_clock();
        time_container get_simulation_time();
        bool process_sim_message();
};
#endif