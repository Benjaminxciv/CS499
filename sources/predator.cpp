/*
Name: predator.cpp
Purpose: Class to define predator's functions, such as energy units, reproduction, and genetic traits.
Last edit: 12-3-2019
Last editor: MG
*/


#include "predator.h"

predator::predator(point init_loc, std::string geno, int init_e, int e_output, int e_reprod_min, double m_spd, double maintain_spd,
                    double m_spd_hod, double m_spd_hed, double m_spd_hor, int m_offsprg, double gest_prd, int offsprg_e_lvl, bool baby) :
    genotype(geno),
    max_speed_hod(m_spd_hod),
    max_speed_hed(m_spd_hed),
    max_speed_hor(m_spd_hor),
    max_offspring(m_offsprg),
    gestation_period(gest_prd),
    offspring_energy_level(offsprg_e_lvl),
    is_baby(baby),
    mammal(init_loc, init_e, e_output, e_reprod_min, m_spd, maintain_spd)
{
    string gene1 = genotype.substr(0,2);
    a_homo_dom = (gene1 == "AA");
    a_het_dom = (gene1 == "Aa" || gene1 == "aA");
    a_homo_rec = (gene1 == "aa");

    string gene2 = genotype.substr(3,2);
    s_homo_dom = (gene2 == "SS");
    s_het_dom = (gene2 == "Ss" || gene2 == "sS");
    s_homo_rec = (gene2 == "ss");

    string gene3 = genotype.substr(6,2);
    f_homo_dom = (gene3 == "FF");
    f_het_dom = (gene3 == "Ff" || gene3 == "fF");
    f_homo_rec = (gene3 == "ff");

    is_pregnant = false;
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
Purpose: Handles logic if the predator successfully caught a grazer and attempts to eat it.
Trace: Traces to Epic 3, acceptance criteria 3
Parameters: 2 char that represent the predator's strength genotype(ss, sS, Ss, or SS). 
Returns: bool if the predator ate or if the prey got away.
*/
bool predator::eat_grazer()
{
    //check if the genes are the same
    if(s_homo_dom)
    {
        int dominant_vs_grazer = (rand() %  100 + 1);
        if (dominant_vs_grazer <= 95)
        {
            //grazer dies
            return true;
        }
        else 
        {
            //grazer lives
            return false;
        }
    }
    //predator is ss.
    //means 50% of eating grazer
    else if(s_homo_rec)
    {
        int recessive_vs_grazer = success_generator();
        //predator was successful
        if ((recessive_vs_grazer == 1) || (recessive_vs_grazer == 2))
        {
            return true;
        }
        else
        {
            //predator lost grazer
            return false;
        }   
    }
    //means predator is sS or Ss
    //means 75% success of eating grazer
    else if(s_het_dom)
    {
        int hetero_vs_grazer = success_generator();
        //if true, predator failed
        if (hetero_vs_grazer == 1)
        {
            return false;
        }
        //predator got grazer
        else
        {
            return true;
        }
    }
    else
    {
        //handle error checking
        return false;
    }
}

/*
Name: success_generator()
Purpose: Handles logic if the predator succeeds or not based on odds. Most odds for predators are
        25/75 split or 50/50 split. 
Trace: Traces to Epic 3, acceptance criteria 3
Parameters: N/A
Returns: int between 1 and 4. In 25/75 split 1=25% event and 2,3,or 4=75%. 
        In 50/50 split 1,2=pass and 3,4=failed.
*/
int predator::success_generator()
{
    int randomized_number = (rand() %  4 + 1);
    return randomized_number;
}

void predator::aggression_food_check(point obj_loc, point& food, point& danger)
{
    if(a_homo_dom)
    {
        if(location.distance(location, obj_loc) < location.distance(location, food))
        {
            food = obj_loc;
        }
    }
    else if(a_het_dom)
    {
        //energy level of 25 or less chosen because that constitutes starving
        //same energy level used in grazers when starving
        if(food.x_loc == -1 && energy <= 25)
        {
            food = obj_loc;
        }
    }
    else if(a_homo_rec)
    {
        danger = obj_loc;
    }
    else
    {
        //add error logging
    }
}

void predator::act()
{
    map<point, string> things_in_sight = sight(150);
    sim_message& message = sim_message::get_instance(false);
    map<point, int> ids_in_sight;
    point danger(-1, -1);
    point g_food(-1, -1);
    point p_food(-1, -1);

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
        else if(x.second == "grazer")
        {
            if(g_food.x_loc == -1 || (location.distance(location, x.first) < location.distance(location, g_food)))
            {
                g_food = x.first;
            }
        }
        else if(x.second == "predator")
        {
            int cell_id = ids_in_sight[x.first];
            if(children.find(cell_id) != children.end())
            {
                continue;
            }
            aggression_food_check(x.first, p_food, danger);
        }
    }

    map<point, string> things_in_smell = smell(25);
    for (auto const& x : things_in_smell)
    {
        if(x.second == "grazer")
        {
            if(g_food.x_loc == -1 || (location.distance(location, x.first) < location.distance(location, g_food)))
            {
                g_food = x.first;
            }
        }
        else if(x.second == "predator")
        {
            int cell_id = ids_in_sight[x.first];
            if(children.find(cell_id) != children.end())
            {
                continue;
            }
            aggression_food_check(x.first, p_food, danger);
        }
    }

    message = sim_message::get_instance();
    message.get_current_time();
    current_time = message.get_time_info();

    map<int, time_container>::iterator child_it;
    for(child_it = children.begin(); child_it != children.end();)
    {
        if(current_time > child_it->second)
        {
            child_it = children.erase(child_it);
        }
        else
        {
            ++child_it;
        }
    }

    if(!is_pregnant && ready_to_reproduce())
    {
        sim_message& message = sim_message::get_instance();
        point mate(-1,-1);
        if(p_food.x_loc != -1)
        {
            mate = p_food;
        }
        else if(danger.x_loc != -1)
        {
            mate = danger;
        }
        if(mate.x_loc != -1)
        {
            if(location.distance(location, mate) <= 5)
            {
                if(message.request_reproduce(p_food, this))
                {
                    is_pregnant = true;
                    double gest_period_hours = 24*gestation_period;
                    if(gest_period_hours > 1)
                    {
                        message.get_future_time(0,0,gest_period_hours);
                    }
                    else
                    {
                        message.get_future_time(0,gest_period_hours*60);
                    }
                    
                    time_container baby_timer = message.get_time_info();
                    babies.push_back(baby_timer);
                }
            }
            else
            {
                dir = find_direction(mate);
            }
        }
    }

    if(danger.x_loc != -1 && !ready_to_reproduce())
    {
        dir = invert_dir();
    }
    else if(g_food.x_loc != -1)
    {
        if(g_food.distance(g_food, location) <= 5)
        {
            if(eat_grazer())
            {
                if(message.eat_organism(g_food))
                {
                    int energy_to_gain = message.get_organism_energy();
                    energy = energy += (energy_to_gain * .90);
                }
            }
            return;
        }
        else
        {
            dir = find_direction(g_food);
        }
    }
    else if(p_food.x_loc != -1 && !ready_to_reproduce())
    {
        if(p_food.distance(p_food, location) <= 5)
        {
            if(message.eat_organism(p_food, this))
            {
                int energy_to_gain = message.get_organism_energy();
                energy = energy += (energy_to_gain * .90);
            }
            else
            {
                message.die(this);
            }
            return;
        }
        else
        {
            dir = find_direction(p_food);
        }
    }

    if(babies.size() > 0)
    {
        if(current_time >= babies[0])
        {
            is_pregnant = false;
            message = sim_message::get_instance();
            message.request_birth(id, location);
            babies.erase(babies.begin());
        }
    }
    banked_moves += float(current_speed/60);
    move();
    if(energy <= 0)
    {
        message.die(this);
    }
}

bool predator::get_s_homo_dom()
{
    return s_homo_dom;
}

bool predator::get_s_het_dom()
{
    return s_het_dom;
}

bool predator::get_s_homo_rec()
{
    return s_homo_rec;
}