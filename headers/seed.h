/*
Name: seed.h

Purpose: Header file for seed pods. 
Last edit: 12-3-2019
Last editor: MG
*/

#ifndef SEED_H
#define SEED_H

#include <string>
#include <iostream>
#include "environment_object.h"
#include <stdlib.h>
#include "clock.h"
#include "simulation.h"
#include "plant.h"


class seed : public environment_object
{
    private:
        int seed_x, seed_y;
        time_container retained_future_time;
        bool retained_future_time_set;

    public:
        seed(point);
        ~seed();
        void seed_grow();
        void act();
        std::string get_type();
        int print_self();
};

#endif