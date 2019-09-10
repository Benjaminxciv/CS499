#include <environment_object.h>

environment_object::environment_object(int init_x_loc, int init_y_loc)
{
    point* init_point = new point;
    init_point->x_loc = init_x_loc;
    init_point->y_loc = init_y_loc;
    this->location = init_point;
}

environment_object::~environment_object()
{
    delete this->location;
}

point* environment_object::get_loc()
{
    return this->location;
}

void environment_object::set_location(int set_x_loc, int set_y_loc)
{
    this->location->x_loc = set_x_loc;
    this->location->y_loc = set_y_loc;
}
