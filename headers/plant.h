/*
Name: plant.h
Purpose: Header file for plants.
Last edit: 09-29-2019
Last editor: MG
*/

#ifndef PLANT_H
#define PLANT_H

#include <string>
#include "environment_object.h"
#include <iostream>

class plant : public environment_object
{
    private:
    public:
        plant(int, int);
        ~plant();
        std::string get_type();
        int print_self();
};

#endif