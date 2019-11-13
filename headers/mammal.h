/*
Name: mammal.h
Purpose: Header file for mammal.cpp.
Last edit: 10-27-2019
Last editor: BP
*/

#ifndef MAMMAL_H
#define MAMMAL_H

#include "environment_object.h"

enum direction {up = 1, up_right = 2, right = 3, down_right = 4, down = 5, down_left = 6, left = 7, up_left = 8};

class mammal : public environment_object
{
    private:
        int energy;
        int e_output;
        double movement_speed;
    public:
        mammal(point, int);
        mammal();
        ~mammal();
        void gain_energy(int);
        void move(direction, int);
        void reproduce();
};

#endif