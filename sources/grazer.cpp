/*
Name: grazer.cpp
Purpose: Grazer's class that defines their EU consumption and reproduction information.
Last edit: 10-27-2019
Last editor: BP
*/

#include "grazer.h"

grazer::grazer(int init_x_loc, int init_y_loc, int init_energy, int energy_input)
    : mammal(init_x_loc, init_y_loc, init_energy)
{
    this->energy_input      = energy_input;
    this->danger            = false;
    this->food_available    = false;
    this->eat_timer         = 0;
}

grazer::~grazer()
{

}

std::string grazer::get_type() 
{
    return "grazer";
}

/*
Name: print_self()
Purpose: everytime it is called, it returns to environment_object this symbol.
Trace: Traces to Epic 2, acceptance criteria 2
Parameters: N/A
Returns: string with at symbol
*/
int grazer::print_self()
{
    std::cout << "@";
    return 0;
}

/*Name: eat()
Purpose: gain energy per minute. Amount gained is determined by enenergy input
Parameters: N/A
BP 10/30/19
*/
void grazer::eat()
{
    this->eat_timer++;

    if(this->eat_timer >= 600)
    {
        reset_eat_timer();
        std::cout << "Moving" << std::endl;
        return;
    }
    
    else if(this->eat_timer >= 60)
    {
      this->gain_energy(energy_input);
    }

    else
    {
        std::cout << "Moving" <<std::endl;
    }
}


void grazer::act()
{
    //Add function call to check if grazer if predator or food is nearby 
    if(this->danger)
    {
        reset_eat_timer();
        std::cout << "Evade" << std::endl;
        this->movement_timer--;
    }

    else if(this->food_available)
    {
        reset_movement_timer();
        eat();
    }
    
    else 
    {
        std::cout << "Move" << std::endl;
        this->movement_timer--;
    }
}


/*Name: reset_eat_timer()
Purpose: reset eat_timer member variable to zero
Parameters: N/A
BP 10/31/19
*/
void grazer::reset_eat_timer()
{
    this->eat_timer = 0;
}

/*Name: reset_movement_timer()
Purpose: reset movement_timer member variable to the time a grzer can maintain max speed
Parameters: N/A
BP 10/31/19
*/
void grazer::reset_movement_timer()
{
    this->movement_timer = (this->maintain_time)*60;
    std::cout<<this->movement_timer;
}


/*Name: set_maintain_gime(int maintain_time)
Purpose: set how long a grazer can run at maxspeed
Parameters: 
	maintain_time: int
		The value in minutes that a grazer can run at maxspeed
BP 10/31/19
*/
void grazer::set_maintain_time(int maintain_time)
{
    this->maintain_time = maintain_time;
    reset_movement_timer();
}