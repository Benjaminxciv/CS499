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
        int movement_timer;
        double movement_count;
        double init_speed;
        double curr_speed;
        int maintain_time;
        bool danger;
        bool food_available;


    public:
        grazer(int, int, int, int);
        ~grazer();
        std::string  get_type() override;
        int print_self();
        void set_energy(int);
        void act() override;
        void eat();
        void reset_eat_timer();
        void store_speed();
        void reset_speed();
        void reset_movement_timer();
        void set_maintain_time(int);
        void limit_movement();
        void check_energy();
        
};
#endif