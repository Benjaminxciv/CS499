#include "grazer.h"

grazer::grazer(int init_x_loc, int init_y_loc) : environment_object(init_x_loc, init_y_loc)
{

}

grazer::~grazer()
{

}

std::string grazer::get_type()
{
    return "grazer";
}