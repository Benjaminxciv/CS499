#include "dmco.h"

dmco::dmco(int init_x_loc, int init_y_loc) : environment_object(init_x_loc, init_y_loc)
{

}

dmco::~dmco()
{

}

std::string dmco::get_type()
{
    return "dmco";
}