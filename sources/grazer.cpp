/*
Name: grazer.cpp
Purpose: Grazer's class that defines their EU consumption and reproduction information.
Last edit: 10-27-2019
Last editor: BP
*/

#include "grazer.h"

grazer::grazer(int init_x_loc, int init_y_loc, int init_energy, int energy_input)
    : environment_object(init_x_loc, init_y_loc), mammal(init_energy)
{
    this -> energy_input = energy_input;
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

/*Name: eat(int)
Purpose: gain energy per minute of eating at the rate of energy input 
Parameters: 
    time_eating: int
        time in minutes a grazer object has been consectutively eating 
Last edit:
    BP 10/27/19
*/
void grazer::eat(int time_eating)
{  
    int energy = this -> energy_input  * time_eating;

    if(time_eating >= 10)
    {
        return;
    }

    this->gain_energy(energy);
}