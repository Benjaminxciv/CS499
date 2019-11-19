/*
Name: mammal.h
Purpose: Header file for mammal.cpp.
Last edit: 10-27-2019
Last editor: BP
*/

#ifndef MAMMAL_H
#define MAMMAL_H

#include "environment_object.h"
#include "sim_message.h"


class mammal : public environment_object
{
    protected:
        enum direction {up = 1, up_right = 2, right = 3, down_right = 4, down = 5, down_left = 6, left = 7, up_left = 8};
        int energy;
        int energy_output;
        int energy_reproduce_min;
        double max_speed;
        double maintain_speed;
        int du_moved;
    public:
        mammal(point, int, int, int, double, double);
        mammal();
        ~mammal();
        int get_energy();
        void set_energy(int);
        bool move(direction, int);
        void set_speed(double);
        int get_speed();
        void gain_energy(int);
        void reproduce();
        bool ready_to_reproduce();
};

#endif