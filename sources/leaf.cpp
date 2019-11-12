/*
Name: leaf.cpp
Purpose: Class containing definitions for leaf environment_object.
Last edit: 11-11-2019
Last editor: MG
*/

#include "leaf.h"

leaf::leaf()
{

}

leaf::leaf(int init_x_loc, int init_y_loc) : environment_object(init_x_loc, init_y_loc)
{

}

leaf::~leaf()
{

}

std::string leaf::get_type()
{
    return "plant";
}

void leaf::act()
{

}