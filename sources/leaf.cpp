/*
Name: leaf.cpp
Purpose: Class containing definitions for leaf environment_object.
Last edit: 11-12-2019
Last editor: MG
*/

#include "leaf.h"

leaf::leaf()
{

}

leaf::leaf(point location) : environment_object(location)
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