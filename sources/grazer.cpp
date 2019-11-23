/*
Name: grazer.cpp
Purpose: Grazer's class that defines their EU consumption and reproduction information.
Last edit: 11-18-2019
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
BP 11/18/19
*/
void grazer::eat()
{
     if(current_time == eat_time)
     {
        reset_eat_time();
        //move: this is based on eating all plants in 5du not the grazers sight
     }
    
    if(current_time == gain_energy_time)
    {
        this->energy += energy_input;
        reset_gain_energy_time();
        //call for deletion of leaf
    }
}

void grazer::act()
{
    sim_message& message = sim_message::get_instance();
    message.get_current_time();
    current_time = message.get_time_info();

    if(this->danger)
    {
        reset_eat_time();
        reset_gain_energy_time();
        //request movement : if true increment number of moves
        if(!retained_movement_time)
        {
            start_movement_time();
        }
        
        if(current_time == movement_time)
        {
            //check behind
            this->current_speed *=.75;
            reset_movement_time(); 
        } 
    } 
    else if(this->food_available)
    {
        reset_movement_time();
        this->reset_speed();
        if(!retained_eat_time)
        {
            start_eat_time();
        }
       
        if(!retained_gain_energy_time)
        {
            start_gain_energy_time();
        }
        eat();
    }
    else 
    {
        /*reset_eat_time();
        reset_gain_energy_time();
        //request movement : if true increment number of moves
        //move(up, 1);
        
        if(!retained_movement_time)
        {
            start_movement_time();
        }   

        if(this->energy <= 0)
        {
            sim_message& message = sim_message::get_instance();
            message.die(this);
        }
        else if(ready_to_reproduce())
        {
            sim_message& message = sim_message::get_instance();
            if(message.request_reproduce(location, this))
            {
                energy /= 2;
            }
        }
        else
        {
             move();
        }
        check_energy();
    }
    if (movement_timer.time_min == current_time.time_min)
    {
        this->curr_speed *= .75;       
    }

    this->set_speed(this->curr_speed);*/
    move();
    }

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
        if(current_time == movement_time)
        {
            this->current_speed = this->max_speed*.75;
            reset_movement_time();
        }
        check_energy();
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
    if(this->energy < 25)
    {
        this->move_count++;
    }
    else
    {
        move_count = 0;
    }

    if(this->move_count > 10)
    {
        //message.die(this);
    }
}

/*Name: reset_eat_timer()
Purpose: reset eat_timer member variable to zero
Parameters: N/A
Traces to Epic 3, Acceptance Criteria 2
BP 11/18/19
*/
void grazer::reset_eat_time()
{
    eat_time = {0,0,0};
    retained_eat_time = false;
}

/*Name: reset_movement_time()
Purpose: resets time_container movement_time min, secs, & hours = 0 
Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
BP 11/18/19
*/
void grazer::reset_movement_time()
{
    movement_time = {0,0,0};
    retained_movement_time = false;
}

/*Name: reset_gain_energy_time()
Purpose: resets time_container gain_energy_time min, secs, & hours = 0 
Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
BP 11/18/19
*/
void grazer::reset_gain_energy_time()
{
    gain_energy_time = {0,0,0};
    retained_gain_energy_time = false;
}

/*Name: start_movement_time()
Purpose: Sets movement_time to a future time_container. The future time created uses
            the data file defined maintain_speed
Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
BP 11/18/19
*/
void grazer::start_movement_time()
{
    sim_message& message = sim_message::get_instance();
    message.get_future_time(0,this->maintain_speed);
    message.process_message();
    movement_time = message.get_time_info();
    retained_movement_time = true;
}

/*Name: start_energy_time()
Purpose: Sets energy_time to a future time_container 1 minute from current_time.
Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
BP 11/18/19
*/
void grazer::start_gain_energy_time()
{
    sim_message& message = sim_message::get_instance();
    message.get_future_time(0,1);
    message.process_message();
    gain_energy_time = message.get_time_info();
    retained_gain_energy_time = true;
}

/*Name: start_eat_time()
Purpose: Sets eat_time to a future time_container 10 minutes from current_time.
Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
BP 11/18/19
*/
void grazer::start_eat_time()
{
    sim_message& message = sim_message::get_instance();
    message.get_future_time(0,10);
    message.process_message();
    eat_time = message.get_time_info();
    retained_eat_time = true;

}

/*
Name: sight_on_plant()
Purpose: Add aspect to Grazer's class that the grazer's can see a plant within 150DU.
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
Returns: N/A
*/

void grazer::sight_on_plant()
{
    //get_cell() get all the cells within 150du
    //
}

/*
Name: sight_on_predator()
Purpose: Add aspect of Grazer's class that the grazer can see predators within 25 DU.
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
Returns: N/A
*/

void grazer::sight_on_predator()
{
    //if withing 25 du 
    //get_cell()
    //danger = true
}
