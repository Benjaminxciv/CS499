#ifndef MAMMAL_H
#define MAMMAL_H

#include <vector>
#include <iostream>
#include "environment_object.h"

enum direction {up = 1, up_right = 2, right = 3, down_right = 4, down = 5, down_left = 6, left = 7, up_left = 8};

class mammal : public environment_object
{
    private:
        int energy;
        int e_output;
        int direction;
    public:
        mammal(int);
        ~mammal();
        void set_direction(int dir);
        void move(int);
        void sense_shape(int, int);
        void reproduce();
};

#endif