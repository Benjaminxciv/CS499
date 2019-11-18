/*Name: mammal.cpp
Purpose: Defines the structure for creating mammal objects and their functions: move ,reproduce, & gain_energy
Last edit: 10-27-19/
Last editor: BP*/

#include "mammal.h"

mammal::mammal(point init_loc, int init_e, int e_output, int e_reprod_min, double m_spd, double maintain_spd) :
    energy(init_e),
    energy_output(e_output),
    energy_reproduce_min(e_reprod_min),
    max_speed(m_spd),
    current_speed(m_spd),
    maintain_speed(maintain_spd),
    environment_object(init_loc)
{

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
    switch(dir)
    {
        case up:
            location.y_loc++;
            break;
        case up_right:
            location.x_loc++;
            location.y_loc++;
            break;
        case right:
            location.x_loc++;
            break;
        case down_right:
            location.x_loc++;
            location.y_loc--;
            break;
        case down:
            location.y_loc--;
            break;
        case down_left:
            location.x_loc--;
            location.y_loc--;
            break;
        case left:
            location.x_loc--;
            break;
        case up_left:
            location.x_loc--;
            location.y_loc++;
            break;
    }
    this->energy -= this->energy_output * (speed / 5);
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
    return this->current_speed;
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
    this->maintain_speed = max_speed;

}
bool mammal::ready_to_reproduce()
{
    return energy >= energy_reproduce_min;
}

int mammal::get_maintain_speed()
{
    return this->maintain_speed;
}

void mammal::set_current_speed(double speed)
{
    this->current_speed = speed;
}

/*
Name: reset_speed()
Purpose: Resets the current speed with the initial speed given
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
Returns: N/A
*/
void mammal::reset_speed()
{
    this->current_speed = max_speed;
}

double mammal::get_max_speed()
{
    return this->max_speed;
}