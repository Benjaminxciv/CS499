/*
Name: predator.h
Purpose: Header file for predators.
Last edit: 09-29-2019
Last editor: MG
*/

#ifndef PREDATOR_H
#define PREDATOR_H

#include "environment_object.h"
#include "mammal.h"

class predator : public environment_object, public mammal
{
    private:
    public:
        predator(int, int, int);
        ~predator();
        std::string get_type();
        int print_self();
};

#endif