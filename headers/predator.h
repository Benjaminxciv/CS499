/*
Name: predator.h
Purpose: Header file for predators.
Last edit: 09-29-2019
Last editor: MG
*/

#ifndef PREDATOR_H
#define PREDATOR_H

#include "mammal.h"

class predator : public mammal
{
    private:
        double max_speed_hod;
        double max_speed_hed;
        double max_speed_hor;
        int max_offspring;
        int gestation_period;
        int offspring_energy_level;
    public:
        predator(point, int, int, int, double, double, double, double, double, int, int, int);
        ~predator();
        std::string get_type();
        int print_self();
};

#endif