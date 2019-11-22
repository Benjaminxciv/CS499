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

    sight_cone();

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
        reset_speed();

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
        if(this->energy < 25)
        {
            move_count++;
        }

        if(move_count > 10)
        {   
            message.die(this); 
            return;  
        }

       // if(this->energy <= 0)
        //{
            //sim_message& message = sim_message::get_instance();
            //message.die(this);
        //}
        if(ready_to_reproduce())
        {
            sim_message& message = sim_message::get_instance();
            if(message.request_reproduce(location, this))
            {
                energy /= 2;
            }
        }
        else
        {
            if(move(up, 1))
            {

            }
        }
        cout << "Move" << endl;
    }

    if (movement_timer.time_min == current_time.time_min)
    {
        this->curr_speed *= .75;       
    }

    this->set_speed(this->curr_speed);
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
    if(this->energy < 25)
    {
        move_count++;
    }

    if(move_count > 10)
    {   
        sim_message& die_message = sim_message::get_instance();
        die_message.die(this);   
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

/*
Name: sight_on_predator()
Purpose: Add aspect of Grazer's class that the grazer can see predators within 25 DU.
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
Returns: N/A
*/

void grazer::sight_cone()
{   
    return;
    string predator_check;
    point look_point;
    look_point = get_loc();

    int test_count = 0; 
    for(int i = 0; i < plant_sight_dist; i++)
    {
        for(int j = -i; j <= i; j++)
        {
            test_count++;
            //right
            if(this->looking_direction == 2)
            {
                look_point.x_loc += i;
                look_point.y_loc += j;
                look_check(look_point, i);
            }

            //left
            if(this->looking_direction == 4)
            {
                look_point.x_loc -= i;
                look_point.y_loc += j;
                look_check(look_point, i);
            }

            //up
            if(this->looking_direction == 1)
            {
                look_point.x_loc += j;
                look_point.y_loc += i;
                look_check(look_point, i);
            }

            //down
            if (this->looking_direction == 3)
            {
                look_point.x_loc -= i;
                look_point.y_loc -= j;
                look_check(look_point, i);
            }
        }
    }
}

void grazer::look_check(point pr, int pred_count)
{
    sim_message& look_message = sim_message::get_instance();
    if(look_message.look_at_cell(pr))
    {
        string lookMessage = look_message.get_simulation_response();
        if(pred_count > pred_sight_dist)
        {
            if(lookMessage == "predator")
            {
                danger = true;
            }
        
            if(lookMessage == "plant")
            {
                //eat
            }
        }

        else
        {
            if(lookMessage == "plant")
            {
                //eat
            }
        }
    }
}