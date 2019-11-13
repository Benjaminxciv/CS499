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
        reset_movement_timer();
        reset_speed();
        eat();
    }

    else 
    {
        std::cout << "Move" << std::endl;
        this->movement_timer--;
    }

    if(current_time.time_min = get_future_time(0,3))
    {
        this->curr_speed *= .75;
    }

    this->set_speed(this->curr_speed);
    check_energy();
}


/*
Name: store_speed()
Purpose: Creates an init speed and curr speed to allow the
MAINTAIN_SPEED to be manipulated
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
Returns: N/A
*/
void grazer::store_speed()
{
    this->init_speed = this->get_speed();
    this->curr_speed = this->get_speed();
}

/*
Name: reset_speed()
Purpose: Resets the current speed with the initial speed given
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
Returns: N/A
*/
void grazer::reset_speed()
{   
    this->curr_speed = this->init_speed;
}


/*
Name: check_energy()
Purpose: Add function that ensures after the grazer's energy unit drops below the defined level, 
therefore the grazer cannot move more than 10 Distance Unit.
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
Returns: N/A
*/
void grazer::check_energy()
{
    if(this->get_energy() < 25)
    {
        this->move_count += this->move_count + (1/3)
    }

    if(this->move_count > 10)
        //kill
}


/*Name: reset_eat_timer()
Purpose: reset eat_timer member variable to zero
Parameters: N/A
BP 10/31/19
*/
void grazer::reset_eat_timer()
{
    this->eat_timer = 0;
    //reset movement speed
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