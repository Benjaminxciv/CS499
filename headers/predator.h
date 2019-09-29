/*
Name: predator.h
Purpose: Header file for predators.
Last edit: 09-29-2019
Last editor: MG
*/

#ifndef PREDATOR_H
#define PREDATOR_H

#include "environment_object.h"

class predator : public environment_object
{
    private:
    public:
        predator(int, int);
        ~predator();
        std::string get_type();
        std::string print_self();
};

#endif