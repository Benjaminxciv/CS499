/*
Name: grazer.h
Purpose: Header file for grazers.
Last edit: 10-27-2019
Last editor: BP
*/

#ifndef GRAZER_H
#define GRAZER_H

#include <string>
#include "environment_object.h"
#include "mammal.h"

class grazer : public mammal
{
    private:
    int energy_input;
    int eat_timer;
    bool danger;
    bool food_available;

    public:
        grazer(int, int, int, int);
        ~grazer();
        std::string  get_type() override;
        void set_energy(int);
        int print_self();
        void eat();
        void reset_eat_timer();
        void act() override;
};

#endif