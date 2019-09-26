/*
Name: plant.h
Purpose: Contains all the information specific to plant lifeforms for Life Simulation.
Last edit: 09-25-19
Last editor: MG
*/

#ifndef PLANT_H
#define PLANT_H

#include <string>
#include "environment_object.h"
#include <stdlib.h>
#include <iostream>

class plant : public environment_object
{
    private:
    public:
        plant(int, int);
        ~plant();
        std::string get_type();
        void seed_pod_values();
        

};

#endif