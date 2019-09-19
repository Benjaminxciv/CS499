#include "plant.h"

plant::plant(int init_x_loc, int init_y_loc) : environment_object(init_x_loc, init_y_loc)
{

}

plant::~plant()
{

}

std::string plant::get_type()
{
    return "plant";
}