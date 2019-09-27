#include "dmco.h"

dmco::dmco(int init_x_loc, int init_y_loc, int init_energy) : environment_object(init_x_loc, init_y_loc), mammal(init_energy)
{

}

dmco::~dmco()
{

}

std::string dmco::get_type()
{
    return "dmco";
}