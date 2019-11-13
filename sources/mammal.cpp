/*Name: mammal.cpp
Purpose: Defines the structure for creating mammal objects and their functions: move ,reproduce, & gain_energy
Last edit: 10-27-19/
Last editor: BP*/

#include "mammal.h"

mammal::mammal(int init_x_loc, int init_y_loc, int init_energy) : environment_object(init_x_loc, init_y_loc)
{
    this->energy = init_energy;
}

mammal::mammal()
{

}

mammal::~mammal()
{
    
}

/*Name: gain_energy(int)
Purpose: generic way for mammals gain energy 
Parameters: 
    energy: int
        number of energy units to add to a mammal objects energy level
Last edit:
    BP 10/27/19
*/
void mammal::gain_energy(int energy)
{
    this->energy += energy;
}

void mammal::move(direction dir, int speed)
{
    point* curr_loc = this->get_loc();
    switch(dir)
    {
        case up:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case up_right:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case right:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case down_right:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case down:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case down_left:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case left:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case up_left:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
    }
    this->energy -= this->e_output * (speed / 5);
}

void mammal::reproduce()
{

}


/*
Name: get_energy()
Purpose: return the energy of the mammal
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
Returns: energy
*/
int mammal::get_energy()
{
    return this->energy;
}


/*
Name: get_speed()
Purpose: returns the movement speed
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
Returns: movement_speed
*/
int mammal::get_speed()
{
    return this->movement_speed;
}


/*
Name: set_speed()
Purpose: sets a speed that is passed in to the current speed of mammal
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: max_speed
Returns: N/A
*/
void mammal::set_speed(double max_speed)
{
    this->movement_speed = max_speed;
}