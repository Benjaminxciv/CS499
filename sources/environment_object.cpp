
/*Name: environment_object.cpp
Purpose: Defines the basic object for the simulation, which holds any shared attributes for all objects
Last edit: 12-3-19
Last editor: MG*/

#include "environment_object.h"

int environment_object::next_id = 1;

environment_object::environment_object()
{
    
}

environment_object::environment_object(point init_loc) //: location (init_loc)
{
    id = next_id++;
    this->location = init_loc;
    garbage = false;
}

environment_object::~environment_object()
{

}

bool environment_object::is_garbage()
{
    return garbage;
}

void environment_object::become_garbage()
{
    garbage = true;
}

/*Name: get_loc
Purpose: Get the X and Y location of the object
Parameters: 
    NA
Returns: Pointer to a point structure containing X and Y location*/
point environment_object::get_loc()
{
    return this->location;
}

/*Name: set_location
Purpose: Set the X and Y location of the objectz
Parameters: 
    x_loc: int
        X location of cell to access
    y_loc: int
        Y location of cell to access
    environ_obj: environment_object*
        Resident to place in the cell
Returns: NA*/
void environment_object::set_location(point loc)
{
    location = loc;
}

int environment_object::get_id()
{
    return id;
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
int environment_object::print_self()
{
    std::cout << " ";
    return 0;
}