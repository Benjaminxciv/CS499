#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include "grid.h"
#include "boulder.h"
#include "LifeSimDataParser.h"
#include <vector>

enum tick_speeds {x1 = 1, x10 = 10, x50 = 50, x100 = 100};

class simulation
{
    private:
        int tick_speed;
        int world_height;
        int world_width;
    public:
        simulation();
        ~simulation();
        void init_sim();
        void run_sim();
        void set_tick_speed(int);
        void increase_tick_speed();
        std::vector<environment_object*> iterate_cells();
};

#endif