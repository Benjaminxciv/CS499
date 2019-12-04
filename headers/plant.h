
/*
Name: plant.h

Purpose: Header file for plants.
Last edit: 12-3-19
Last editor: MG
*/

#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <iostream>
#include <vector>
#include "environment_object.h"
#include <stdlib.h>
#include "clock.h"
#include "sim_message.h"
#include "seed.h"
#include "leaf.h"

class plant : public environment_object
{
    private:
        double growth_rate;
        int max_size;
        int max_seed_cast_dist;
        int max_seed_num;
        int initial_plant_size;
        double seed_viability;
        int current_size;
        time_container retained_future_time;
        bool retained_future_time_set;
        vector<int> list_of_leaves;
    public:
        plant(point, double, int, int, int, double, int);
        ~plant();
        std::string get_type();
        int print_self();
        int get_current_size();
        int get_max_size();
        void grow();
        void set_seed_pod_values();
        void radially_disperse_seed();
        void act();
};

#endif
