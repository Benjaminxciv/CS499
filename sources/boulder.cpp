/*
Name: boulder.cpp
Purpose: Header file for grazers.
Last edit: 09-29-2019
Last editor: MG
*/

#include "boulder.h"

boulder::boulder(int init_x_loc, int init_y_loc) : environment_object(init_x_loc, init_y_loc)
{

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