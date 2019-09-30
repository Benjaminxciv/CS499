#include "environment_object.h"

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

/*Name: get_loc
Purpose: Get the X and Y location of the object
Parameters: 
    NA
Returns: Pointer to a point structure containing X and Y location*/
point* environment_object::get_loc()
{
    return this->location;
}

/*Name: set_location
Purpose: Set the X and Y location of the objectz
Parameters: 
    x_loc: int
        X location of cell to access
    y_loc: int
        Y location of cell to access
    environ_obj: environment_object*
        Resident to place in the cell
Returns: NA*/
void environment_object::set_location(int set_x_loc, int set_y_loc)
{
    this->location->x_loc = set_x_loc;
    this->location->y_loc = set_y_loc;
}

void environment_object::act()
{

}

std::string environment_object::get_type()
{
    return "";
}