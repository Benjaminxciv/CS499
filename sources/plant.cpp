/*
Name: plant.cpp
Purpose: Class defining all the plant's function, such as location and growing pattern.
Last edit: 09-29-2019
Last editor: MG
*/

#include "plant.h"

plant::plant(int init_x_loc, int init_y_loc) : environment_object(init_x_loc, init_y_loc)
{

}

plant::~plant()
{

}

std::string plant::get_type()
{
    return "plant";
}

/*
Name: print_self()
Purpose: everytime it is called, it returns to environment_object this symbol.
Trace: Traces to Epic 2, acceptance criteria 2
Parameters: N/A
Returns: string with octothorpe
*/
std::string plant::print_self()
{
    std::string plant_symbol = "#";
    return plant_symbol;

}