/*
Name: plant.h

Purpose: Header file for plants.
Last edit: 09-29-2019
Last editor: AW
*/

#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <iostream>
#include "environment_object.h"
#include <stdlib.h>
#include "sim_message.h"


class plant : public environment_object
{
    private:
    public:
        plant(point);
        ~plant();
        std::string get_type();
        int print_self();
        void set_seed_pod_values();
        void seed_grow();
        void act();
};

#endif