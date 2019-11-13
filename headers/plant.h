
/*
Name: plant.h

Purpose: Header file for plants.
Last edit: 11-12-2019
Last editor: MG
*/

#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <iostream>
#include "environment_object.h"
#include <stdlib.h>
#include "clock.h"
#include "sim_message.h"
#include "seed.h"

class plant : public environment_object
{
    private:
        int plant_x, plant_y, seed_pod_distance, seed_pod_seed_number;
        LifeSimDataParser *info_gather;
        time_container current_time;
        time_container future_time;
    public:
        plant();
        plant(int, int);
        ~plant();
        std::string get_type();
        int print_self();
        void set_seed_pod_values();
        void radially_disperse_seed();
        void act();
};

#endif
