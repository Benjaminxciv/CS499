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
        void store_speed();
        void reset_speed();
        direction invert_dir();
        

    public:
        grazer(point, int, int, int, int, double, double);
        ~grazer();
        string  get_type() override;
        int print_self();
        void act() override;

        void check_energy();
        void sight_cone();
        void look_check(point, int);
        
};
#endif