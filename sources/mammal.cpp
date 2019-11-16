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

int mammal::get_energy()
{
    return energy;
}

bool mammal::move(direction dir, int speed)
{
    sim_message& message = sim_message::get_instance();
    point move_to = location;
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
    //this->energy -= this->energy_output * (speed / 5);
    return true;
}

void mammal::reproduce()
{

}

bool mammal::ready_to_reproduce()
{
    return energy >= energy_reproduce_min;
}