/*
Name: predator_factory.h
Purpose: Header file for Abstract factory that houses genetics for predators. 
Last edit: 11-11-2019
Last editor: MG
*/

#include "sim_message.h"
#include "stdio.h"
#include "math.h"
#include "time.h"

#ifndef PREDATOR_FACTORY_H
#define PREDATOR_FACTORY_H

class predator_factory
{
    private:

    public:
    predator_factory();
    ~predator_factory();
    char predator_factory::punnett_square(char, char);
};

#endif