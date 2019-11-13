/*
Name: predator.cpp
Purpose: Class to define predator's functions, such as energy units, reproduction, and genetic traits.
Last edit: 09-29-2019
Last editor: MG
*/


#include "predator.h"

predator::predator(point init_loc, int init_energy) : mammal(init_loc, init_energy)
{

}

predator::~predator()
{

}

std::string predator::get_type()
{
    return "predator";
}

/*
Name: print_self()
Purpose: everytime it is called, it returns to environment_object this symbol.
Trace: Traces to Epic 2, acceptance criteria 2
Parameters: N/A
Returns: string with an asterisk
*/
int predator::print_self()
{
    std::cout << "*";
    return 0;

}