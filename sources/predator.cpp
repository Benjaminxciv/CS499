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

}

predator::~predator()
{

}

point predator::smell()
{
    vector<point> points_to_check;
    int diameter = 25;
    int radius = (diameter-1)/2;
    for (int y = radius; y >= 0; y--)
    {
        for(int x = 0; x <= (radius-y)*2; x++)
        {
            point p(location.x_loc-x, location.y_loc-y);
            points_to_check.push_back(p);
        }
    }
    for (int y = 1; y <= radius; y++)
    {
        for(int x = 0; x <= (radius-y)*2; x++)
        {
            point p(location.x_loc+x, location.y_loc+y);
            points_to_check.push_back(p);
        }
    }
    sim_message& message = sim_message::get_instance();
    point grazer_loc = location;
    message.look_at_cell(grazer_loc, points_to_check);
    map<point, std::string> cell_map = message.get_multiple_responses();
    for (auto const& cell : cell_map)
    {
        if(cell.second == "grazer")
        {
            grazer_loc = cell.first;
        }
    }
    return grazer_loc;
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