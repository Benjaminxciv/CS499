/*
Name: boulder.cpp
Purpose: Header file for grazers.
Last edit: 09-29-2019
Last editor: MG
*/

#include "boulder.h"

/*
Name: boulder(int, int, int, int)
Purpose: Set the location and height from data file
Trace: Traces to Epic 2, Acceptance Criteria 2
Parameters: x location, y location, diameter, height
Returns: N/A
*/

boulder::boulder(point init_loc, int diameter, int height) : environment_object(init_loc)
{
    this->diameter = diameter;
    this->height = height;
}

boulder::~boulder()
{

}

std::string boulder::get_type()
{
    return "boulder";
}

/*
Name: print_self()
Purpose: everytime it is called, it returns to environment_object this symbol.
Trace: Traces to Epic 2, acceptance criteria 2
Parameters: N/A
Returns: string with an asterisk
*/
int boulder::print_self()
{
    std::cout << "O";
    return 0;

}
