/*
Name: grazer.h
Purpose: Header file for grazers.
Last edit: 10-27-2019
Last editor: BP
*/

#ifndef GRAZER_H
#define GRAZER_H

#include <string>
#include "environment_object.h"
#include "mammal.h"

class grazer : public environment_object, public mammal
{
    private:
    int energy_input;
    public:
        grazer(int, int, int, int);
        ~grazer();
        std::string  get_type() override;
        void set_energy(int);
        int print_self();
        void eat(int);
};

#endif