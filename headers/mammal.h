#ifndef MAMMAL_H
#define MAMMAL_H

#include "environment_object.h"

enum direction {up = 1, up_right = 2, right = 3, down_right = 4, down = 5, down_left = 6, left = 7, up_left = 8};

class mammal : public environment_object
{
    private:
        int energy;
        int e_output;
    public:
        mammal(int);
        ~mammal();
        void move(direction, int);
        void reproduce();
};

#endif