/*
Name: leaf.cpp
Purpose: Class containing definitions for leaf environment_object. Leaf inhertis from environment_object and used to show plant's growth.
Last edit: 12-3-2019
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
    return "leaf";
}

void leaf::act()
{

}