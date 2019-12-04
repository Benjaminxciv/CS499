/*
Name: mammal.h
Purpose: Header file for mammal.cpp.
Last edit: 12-3-2019
Last editor: BP
*/

#ifndef MAMMAL_H
#define MAMMAL_H

#include <vector>
#include <iostream>
#include "environment_object.h"
#include "sim_message.h"

class mammal : public environment_object
{
    protected:
        enum direction {up = 1, up_right = 2, right = 3, down_right = 4, down = 5, down_left = 6, left = 7, up_left = 8};
        direction dir;
        int energy;
        int energy_output;
        int energy_reproduce_min;
        double max_speed;
        double current_speed;
        double maintain_speed;
        int du_moved;
        float banked_moves;
        vector<point> vision_points;
        bool restrict_sight_boulder(vector<point>, point);
        direction invert_dir();
    public:
        mammal(point, int, int, int, double, double);
        mammal();
        ~mammal();
        void set_direction(direction);
        void move(int);
        int get_energy();
        void gain_energy(int);
        void set_energy(int);
        int move();
        bool try_move();
        void set_speed(double);
        void reproduce();
        void set_current_speed(double);
        void reset_speed();
        bool ready_to_reproduce();
        map<point, string> sight(int);
        map<point, string> smell(int);
        direction find_direction(point);
        int get_energy_reproduce_min();
        vector<point> get_vision_points();
};

#endif