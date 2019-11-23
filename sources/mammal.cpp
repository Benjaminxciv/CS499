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
    maintain_speed(maintain_spd),
    environment_object(init_loc)
{
    du_moved = 0;
}

mammal::mammal()
{

}

mammal::~mammal()
{
    
}

void mammal::set_direction(int dir)
{
    direction = dir;
}

/*Name: gain_energy(int)
Purpose: generic way for mammals gain energy 
Parameters: 
    energy: int
        number of energy units to add to a mammal objects energy level
Last edit:
    BP 10/27/19
*/
void mammal::gain_energy(int added_energy)
{
    energy += added_energy;
}

void mammal::set_energy(int new_energy)
{
    energy = new_energy;
}

bool mammal::move()
{
    sim_message& message = sim_message::get_instance();
    point move_to = location;
    switch(direction)
    {
        case up:
            move_to.y_loc++;
            if(message.move_organism(move_to, this))
            {
                location.y_loc++;
            }
            else
            {
                return false;
            }
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
    du_moved++;
    if(du_moved >= 5)
    {
        du_moved = 0;
        energy -= energy_output;
    }
    return true;
}

void mammal::sense_shape(int sides, int side_size)
{
    
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
    return this->maintain_speed;
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