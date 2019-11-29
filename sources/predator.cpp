/*
Name: predator.cpp
Purpose: Class to define predator's functions, such as energy units, reproduction, and genetic traits.
Last edit: 09-29-2019
Last editor: MG
*/


#include "predator.h"

predator::predator(point init_loc, std::string geno, int init_e, int e_output, int e_reprod_min, double m_spd, double maintain_spd,
                    double m_spd_hod, double m_spd_hed, double m_spd_hor, int m_offsprg, int gest_prd, int offsprg_e_lvl) :
    genotype(geno),
    max_speed_hod(m_spd_hod),
    max_speed_hed(m_spd_hed),
    max_speed_hor(m_spd_hor),
    max_offspring(m_offsprg),
    gestation_period(gest_prd),
    offspring_energy_level(offsprg_e_lvl),
    mammal(init_loc, init_e, e_output, e_reprod_min, m_spd, maintain_spd)
{
    banked_moves = 0;
}

predator::~predator()
{

}

std::string predator::get_type()
{
    return "predator";
}

/*
Name: print_self()
Purpose: everytime it is called, it returns to environment_object this symbol.
Trace: Traces to Epic 2, acceptance criteria 2
Parameters: N/A
Returns: string with an asterisk
*/
int predator::print_self()
{
    std::cout << "*";
    return 0;

}

int predator::get_max_offspring()
{
    return max_offspring;
}

std::string predator::get_genotype()
{
    return genotype;
}


/*
Name: eat()
Purpose: calls sim_message wrapper to an organism, then calls sim_message's get_organism_energy 
    then reduces the energy returned to 90% and adds it to the predators energy
Trace: Traces to Epic 3, Acceptance Criteria 3
Parameters: point food_location
    desc: the point/location of the organism the predator is 
    trying to eat.
*/
void predator::eat(point food_location)
{   
    sim_message &message = sim_message::get_instance();
    if(message.eat_organism(food_location))
    {
        int energy_to_gain = message.get_organism_energy();
        this->energy = this->energy+= (energy_to_gain * .90);
    }

}

void predator::act()
{
    map<point, string> things_in_sight = sight(150);
    //return;   
    point danger(-1, -1);
    point food(-1, -1);

    point left(-1, -1);
    point right(-1, -1);
    point middle(-1, -1);

    for (auto const& x : things_in_sight)
    {
        if(x.second == "grazer" && food.x_loc == -1)
        {
            food = x.first;
        }
    }

    map<point, string> things_in_smell = smell(25);
    for (auto const& x : things_in_smell)
    {
        if(x.second == "grazer" && food.x_loc == -1)
        {
            food = x.first;
        }
    }

    sim_message& message = sim_message::get_instance();
    message.get_current_time();
    current_time = message.get_time_info();

    if(food.x_loc != -1)
    {
        //if(food.distance(food, location) <= 5)
        //{
        //    //return;
        //}
        //else
        //{
            dir = find_direction(food);
        //}
    }

    //move this between running from preds & before eating
    if(ready_to_reproduce())
    {
        sim_message& message = sim_message::get_instance();
        if(message.request_reproduce(location, this))
        {
        }
    }
    //loop for move rate
    banked_moves += float(current_speed/60);
    move();
    if(energy <= 0)
    {
        message.die(this);
    }
}