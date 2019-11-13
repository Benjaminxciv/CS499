/*
Name: grazer.h
Purpose: Header file for grazers.
Last edit: 11-7-2019
Last editor: BP
*/

#ifndef GRAZER_H
#define GRAZER_H

#include <string>
#include "environment_object.h"
#include "mammal.h"
#include "sim_message.h"

class grazer : public mammal
{
    private:
        int energy_input;
        time_container current_time;
        time_container eat_timer;
        time_container gain_energy_timer;
        time_container movement_timer;
        int maintain_time;
        bool danger;
        bool food_available;

    public:
        grazer(point, int, int);
        ~grazer();
        std::string  get_type() override;
        int print_self();
        void set_energy(int);
        void act() override;
        void eat();
        void reset_eat_timer();
        void reset_movement_timer();
        void set_maintain_time(int);
        
};
#endif