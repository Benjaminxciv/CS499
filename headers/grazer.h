/*
Name: grazer.h
Purpose: Header file for grazers.
Last edit: 11-18-2019
Last editor: BP
*/

#ifndef GRAZER_H
#define GRAZER_H

#include <string>
#include "mammal.h"

class grazer : public mammal
{
    private:
        int energy_input;
        int move_count;
        time_container current_time;
        time_container eat_time;
        time_container gain_energy_time;
        time_container movement_time;
        time_container danger_time;
        bool retained_movement_time;
        bool retained_gain_energy_time;
        bool retained_eat_time;
        bool retained_danger_time;
        int init_speed;
        int curr_speed;
        bool slowed;
        bool food_in_sight;
        bool danger_in_sight;

        const int eat_reach = 5;
        const int plant_sight_dist = 150;
        const int pred_sight_dist = 25;

        bool eat(point);
        direction invert_dir();

    public:
        grazer(point, int, int, int, int, double, double);
        ~grazer();
        string  get_type() override;
        int print_self();
        void act() override;

        bool found_food();
        bool found_danger();
        
};
#endif