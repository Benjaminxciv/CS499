#include "predator.h"

predator::predator(int init_x_loc, int init_y_loc, int init_energy) : environment_object(init_x_loc, init_y_loc), mammal(init_energy)
{

}

predator::~predator()
{

}

void predator::smell()
{
    //smell in 25 DU radius
    //send message up to sim asking for cells within 25 DU
    //found_direction = sim->get_cells()
    int found_direction = 0;
    if(found_direction)
    {
        this->set_direction(found_direction);
    }
}

std::string predator::get_type()
{
    return "predator";
}