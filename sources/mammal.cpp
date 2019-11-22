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
    du_moved = 0;
}

mammal::mammal()
{

}

mammal::~mammal()
{
    
}

void mammal::set_energy(int new_energy)
{
    energy = new_energy;
}

bool mammal::move(direction dir, int speed)
{
    sim_message& message = sim_message::get_instance();
    point move_to = location;
    
    if(dir == up || up_left || up_right)
        looking_direction = 1;
    else if(dir == right)
        looking_direction = 2;
    else if(dir == down || down_left || down_right)
        looking_direction = 3;
    else
        looking_direction = 4;

    switch(dir)
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
