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
        double move_count;
        time_container current_time;
        time_container eat_time;
        time_container gain_energy_time;
        time_container movement_time;      
        bool retained_movement_time;
        bool retained_gain_energy_time;
        bool retained_eat_time;
        bool danger;
        bool food_available;

        const int eat_reach = 5;
        const int plant_sight_dist = 150;
        const int pred_sight_dist = 25;

        void start_movement_time();
        void start_eat_time();
        void start_gain_energy_time();
        void reset_movement_time();
        void reset_gain_energy_time();
        void reset_eat_time();
        void eat();

    public:
        grazer(point, int, int, int, int, double, double);
        ~grazer();
        string  get_type() override;
        int print_self();
        void act() override;

        void check_energy();
        void sight_on_plant();
        void sight_on_predator();
        
};
#endif