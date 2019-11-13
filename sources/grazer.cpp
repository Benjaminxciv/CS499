/*
Name: grazer.cpp
Purpose: Grazer's class that defines their EU consumption and reproduction information.
Last edit: 11-7-2019
Last editor: BP
*/

#include "grazer.h"

grazer::grazer(point init_loc, int init_energy, int energy_input) : mammal(init_loc, init_energy)
{
    this->energy_input      = energy_input;
    this->danger            = false;
    this->food_available    = false;
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
Purpose: gain energy per minute. Amount gained is determined by energy input
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
BP 10/30/19
*/
void grazer::eat()
{
     if(current_time.time_min >= eat_timer.time_min )
     {
        reset_eat_timer();
        cout << "Moving" << endl;
        return;
     }
    
    else if(current_time.time_sec == gain_energy_timer.time_sec)
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
    sim_message& message = sim_message::get_instance();
    message.get_current_time();
    message.process_message();
    current_time = message.get_time_info();

    if(this->danger)
    {
        reset_eat_timer();
        if(movement_timer.time_min == 0)
        {
            message.get_future_time(0,this->maintain_time);
            message.process_message();
            movement_timer = message.get_time_info();
        }   
    }

    else if(this->food_available)
    {
        reset_movement_timer();
        if(gain_energy_timer.time_sec == 0)
        {
            message.get_future_time(58);
            message.process_message();
            gain_energy_timer = message.get_time_info();
        }

        if(eat_timer.time_sec == 0)
        {
            message.get_future_time(0, 1);
            message.process_message();
            eat_timer = message.get_time_info();
        }

        eat();
    }
    
    else 
    {
        cout << "Move" << endl;
    }
}

/*Name: reset_eat_timer()
Purpose: reset eat_timer member variable to zero
Parameters: N/A
Traces to Epic 3, Acceptance Criteria 2
BP 11/7/19
*/
void grazer::reset_eat_timer()
{
    eat_timer.time_sec = 0;
    eat_timer.time_min = 0;
}

/*Name: reset_movement_timer()
Purpose: reset movement_timer member variable to the time a grzer can maintain max speed
Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
BP 11/7/19
*/
void grazer::reset_movement_timer()
{
    movement_timer.time_sec = 0;
    movement_timer.time_min = 0;
}


/*Name: set_maintain_time(int maintain_time)
Purpose: set how long a grazer can run at maxspeed
Traces to Epic 3, Acceptance Criteria 2
Parameters: 
	maintain_time: int
		The value in minutes that a grazer can run at maxspeed
BP 11/7/19
*/
void grazer::set_maintain_time(int maintain_time)
{
    this->maintain_time = maintain_time;
}