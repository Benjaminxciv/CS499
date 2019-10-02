#include "mammal.h"

mammal::mammal(int init_energy)
{
    this->energy = init_energy;
}

mammal::~mammal()
{
    
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