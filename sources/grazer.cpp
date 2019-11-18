/*
Name: grazer.cpp
Purpose: Grazer's class that defines their EU consumption and reproduction information.
Last edit: 11-7-2019
Last editor: BP
*/

#include "grazer.h"

grazer::grazer(point init_loc, int init_e, int e_input, int e_output, int e_reprod_min, double m_spd, double maintain_spd) :
    energy_input(e_input),
    mammal(init_loc, init_e, e_output, e_reprod_min, m_spd, maintain_spd)
{
    this->danger                    = false;
    this->food_available            = false;
    this->retained_movement_time    = false;
    this->retained_eat_time         = false;
    this->retained_gain_energy_time = false;
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
     if(current_time == eat_time)
     {
        reset_eat_timer();
        cout << "Moving" << endl;
     }
    
    if(current_time == gain_energy_time)
    {
        this->gain_energy(energy_input);
        reset_gain_energy_time();
        //call for deletion of leaf
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
        reset_gain_energy_time();
        if(!retained_movement_time)
        {
            start_movement_timer();
        }
        
        if(current_time == movement_time)
        {
            //check behind
            //drop speed to 75% 
        } 
  
    }

    else if(this->food_available)
    {
        reset_movement_timer();
        if(!retained_eat_time)
        {
            start_eat_timer();
        }

        eat();
    }
    
    else 
    {
        reset_eat_timer();
        reset_gain_energy_time();
        move(up, 1);
        if(!retained_movement_time)
        {
            start_movement_timer();
        }   

        if(current_time == movement_time)
        {
            //Drop 75% speed
        }
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
    retained_eat_time = false;
    eat_time = {0,0,0};
}

/*Name: reset_movement_timer()
Purpose: reset movement_timer member variable to the time a grzer can maintain max speed
Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
BP 11/7/19
*/
void grazer::reset_movement_timer()
{
    movement_time = {0,0,0};
    retained_movement_time = false;
}

void grazer::reset_gain_energy_time()
{
    gain_energy_time = {0,0,0};
}


void grazer::start_movement_timer()
{
    // message.get_future_time(0,this->get_maintain_speed);
    // message.process_message();
    // movement_timer = message.get_time_info();
    retained_movement_time = true;
}

void grazer::start_gain_energy_time()
{
    // message.get_future_time(0,1);
    // message.process_message();
    // eat_timer = message.get_time_info();
    retained_gain_energy_time = true;
}

void grazer::start_eat_timer()
{
    // message.get_future_time(0,10);
    // message.process_message();
    // eat_timer = message.get_time_info();
    retained_eat_time = true;
    start_gain_energy_time();
}