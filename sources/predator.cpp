#include "predator.h"

predator::predator(int init_x_loc, int init_y_loc, int init_energy) : environment_object(init_x_loc, init_y_loc), mammal(init_energy)
{

}

predator::~predator()
{

}

std::string predator::get_type()
{
    return "predator";
}