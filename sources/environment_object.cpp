/*
Name: environment_objects.cpp
Purpose: Holds the environment_objects class that boulder, plant, grazer, and predators inherit from.
Last edit: 09-29-2019
Last editor: MG
*/

#include "environment_object.h"

environment_object::environment_object(int init_x_loc, int init_y_loc)
{
    point* init_point = new point;
    init_point->x_loc = init_x_loc;
    init_point->y_loc = init_y_loc;
    this->location = init_point;
}

environment_object::~environment_object()
{
    delete this->location;
}

point* environment_object::get_loc()
{
    return this->location;
}

void environment_object::set_location(int set_x_loc, int set_y_loc)
{
    this->location->x_loc = set_x_loc;
    this->location->y_loc = set_y_loc;
}

void environment_object::act()
{

}

std::string environment_object::get_type()
{
    return "";
}

/*
Name: print_self()
Purpose: virtual fx added to help with console output and prove the file is read in correctly. 
Trace: Traces to Epic 2, acceptance criteria 2 
Parameters: N/A
Returns: string containing the symbol
*/
std::string environment_object::print_self()
{
    return "";
}

