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
        this->gain_energy(this->energy_input);
    }

}

void grazer::act()
{
    //Add function call to check if grazer if predator or food is nearby 

    if(this->danger)
    {
        reset_eat_timer();
        //Predator should evade here
    }

    else if(this->food_available)
    {
        eat();

    }
    
    else 
    {
        std::cout << "Moving" << std::endl;
    }

}

/*Name: reset_timer()
Purpose: reset seconds_timer member variable to zero
Parameters: N/A
    BP 10/30/19
*/
void grazer::reset_eat_timer()
{
    this->eat_timer = 0;
}
