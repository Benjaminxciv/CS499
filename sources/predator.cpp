#include "predator.h"

predator::predator(int init_x_loc, int init_y_loc) : environment_object(init_x_loc, init_y_loc)
{

}

predator::~predator()
{

}

std::string predator::get_type()
{
    return "predator";
}