/*
Name: grazer.cpp
Purpose: Grazer's class that defines their EU consumption and reproduction information.
Last edit: 09-29-2019
Last editor: MG
*/

#include "grazer.h"

grazer::grazer(int init_x_loc, int init_y_loc) : environment_object(init_x_loc, init_y_loc)
{

}

grazer::~grazer()
{

}

std::string grazer::get_type()
{
    return "grazer";
}

/*
Name: print_self()
Purpose: everytime it is called, it returns to environment_object this symbol.
Trace: Traces to Epic 2, acceptance criteria 2
Parameters: N/A
Returns: string with at symbol
*/
int grazer::print_self()
{
    std::cout << "@";
    return 0;

}