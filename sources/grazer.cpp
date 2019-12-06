/*
Name: grazer.cpp
Purpose: Grazer's class that defines their EU consumption and reproduction information.
Last edit: 12-3-19
Last editor: BP
*/
#include "grazer.h"
#include "geometry.h"

grazer::grazer(point init_loc, int init_e, int e_input, int e_output, int e_reprod_min, double m_spd, double maintain_spd) :
    energy_input(e_input),
    mammal(init_loc, init_e, e_output, e_reprod_min, m_spd, maintain_spd)
{
    retained_movement_time = false;
    retained_eat_time = false;
    retained_danger_time = false;
    retained_gain_energy_time = false;
    slowed = false;
    food_in_sight = false;
    move_count = 0;
    danger_in_sight = false;
    banked_cells_to_eat = 0;
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
        banked_cells_to_eat += 0.073;
        retained_movement_time = false;
        curr_speed = init_speed;
        if(banked_cells_to_eat >= 1)
        {
            message.eat_organism(food);
            banked_cells_to_eat--;
        }
        if(!retained_eat_time)
        {
            message.get_future_time(0,10);
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
            retained_gain_energy_time = false;
            return false;
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
        banked_cells_to_eat = 0;
        dir = find_direction(food);
        return false;
    }
    banked_cells_to_eat = 0;
    return false;
}

void grazer::act()
{
    map<point, string> things_in_sight = sight(150);
    point danger(-1, -1);
    point food(-1, -1);

    vector<point> boulder_locs;

    for (auto const& x : things_in_sight)
    {
        if(!restrict_sight_boulder(boulder_locs, x.first))
        {
            continue;
        }
        if(x.second == "boulder")
        {
            boulder_locs.push_back(x.first);
        }
        else if(x.second == "predator" && x.first.distance(x.first, location) <= 25)
        {
            danger = x.first;
            break;
        }
        else if((x.second == "plant" || x.second == "leaf") && !retained_eat_time)
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
        //run away from danger
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
        map<point, string> things_in_smell = smell(5);
        for (auto const& x : things_in_smell)
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
    else
    {
        move_count = 0;
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