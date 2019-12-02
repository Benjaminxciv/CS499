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
    this->retained_movement_time    = false;
    this->retained_eat_time         = false;
    retained_danger_time = false;
    this->retained_gain_energy_time = false;
    banked_moves = 0;
    slowed = false;
    food_in_sight = false;
    move_count = 0;
    danger_in_sight = false;
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
bool grazer::eat(point food)
{
    sim_message& message = sim_message::get_instance();
    int distance = location.distance(location, food);
    if(distance <= 5)
    {
        retained_movement_time = false;
        curr_speed = init_speed;
        if(!retained_eat_time)
        {
            message.get_future_time(1);
            eat_time = message.get_time_info();
            retained_eat_time = true;
        }
        if(!retained_gain_energy_time)
        {
            message.get_future_time(0,1);
            gain_energy_time = message.get_time_info();
            retained_gain_energy_time = true;
        }
        if(current_time >= eat_time)
        {
            retained_eat_time = false;
            message.eat_organism(food);
        }

        if(current_time >= gain_energy_time)
        {
            energy += energy_input;
            retained_gain_energy_time = false;
        }
        return true;
    }
    else
    {
        dir = find_direction(food);
        return false;
    }
    return false;
}

grazer::direction grazer::invert_dir()
{
    switch(dir)
    {
        case up:
            return down;
            break;
        case down:
            return up;
            break;
        case left:
            return right;
            break;
        case right:
            return left;
            break;
        case up_left:
            return down_right;
            break;
        case up_right:
            return down_left;
            break;
        case down_left:
            return up_right;
            break;
        case down_right:
            return up_left;
            break;
    }
    return up;
}

void grazer::act()
{
    map<point, string> things_in_sight = sight(150);
    //return;   
    point danger(-1, -1);
    point food(-1, -1);

    //point left(-1, -1);
    //point right(-1, -1);
    //point middle(-1, -1);
    bool ignore_left = false;
    bool ignore_right = false;
    bool ignore_middle = false;

    for (auto const& x : things_in_sight)
    {
        if(x.second == "boulder")
        {
            direction obj_dir = find_direction(x.first);
            if(obj_dir == left)
            {
                ignore_left = true;
            }
            else if(obj_dir == right)
            {
                ignore_right  = true;
            }
            else if(x.first.x_loc == location.x_loc)
            {
                ignore_middle = true;
            }
        }
        if(x.second == "predator" && x.first.distance(x.first, location) <= 25)
        {
            danger = x.first;
            break;
        }
        if((x.second == "plant" || x.second == "leaf") && !retained_eat_time)
        {
            if(food.x_loc == -1)
            {
                food = x.first;
            }
            if(location.distance(location, x.first) < location.distance(location, food))
            {
                food = x.first;
            }
        }
    }

    sim_message& message = sim_message::get_instance();
    message.get_current_time();
    current_time = message.get_time_info();

    if(danger.x_loc != -1)
    {
        danger_in_sight = true;
        retained_eat_time = false;
        retained_gain_energy_time = false;
        if(!retained_danger_time)
        {
            retained_danger_time = true;
            //need to look at this amount of time
            message.get_future_time(0, 7, 0);
            danger_time = message.get_time_info();
        }
        dir = invert_dir();
    }
    else if(retained_danger_time)
    {
        if(danger_time >= current_time)
        {
            //stop & look behind
            dir = invert_dir();
            retained_movement_time = false;
            retained_danger_time = false;
            slowed = false;
            curr_speed = init_speed;
            return;
        }
    }
    else if(retained_eat_time)
    {
        danger_in_sight = false;
        map<point, string> things_in_smell = smell(25);
        for (auto const& x : things_in_sight)
        {
            if(x.second == "plant" || x.second == "leaf") 
            {
                if(food.x_loc == -1)
                {
                    food = x.first;
                }
                if(location.distance(location, x.first) < location.distance(location, food))
                {
                    food = x.first;
                }
            }
        }
        if(food.x_loc != -1)
        {
            food_in_sight = true;
            if(eat(food))
            {
                return;
            }
        }
    }
    else if(food.x_loc != -1)
    {
        danger_in_sight = false;
        food_in_sight = true;
        if(eat(food))
        {
            return;
        }
    }
    else
    {
        danger_in_sight = false;
        food_in_sight = false;
    }
    
    if(ready_to_reproduce())
    {
        if(message.request_reproduce(location, this))
        {
            energy /= 2;
        }
    }

    if(!retained_movement_time)
    {
        message.get_future_time(0, maintain_speed, 0);
        movement_time = message.get_time_info();
        retained_movement_time = true;
    }
    else
    {
        if(!slowed && current_time >= movement_time)
        {
            current_speed *= .75;
            slowed = true;
        }
    }
    banked_moves += float(current_speed/60);
    int num_moves = move();
    if(energy < 25)
    {
        move_count += num_moves;
        if(move_count >= 10)
        {
            message.die(this);
        }
    }
    if(energy <= 0)
    {
        message.die(this);
    }
}

bool grazer::found_food()
{
    return food_in_sight;
}

bool grazer::found_danger()
{
    return danger_in_sight;
}