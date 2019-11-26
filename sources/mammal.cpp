/*Name: mammal.cpp
Purpose: Defines the structure for creating mammal objects and their functions: move ,reproduce, & gain_energy
Last edit: 10-27-19/
Last editor: BP*/

#include "mammal.h"

mammal::mammal(point init_loc, int init_e, int e_output, int e_reprod_min, double m_spd, double maintain_spd) :
    energy(init_e),
    energy_output(e_output),
    energy_reproduce_min(e_reprod_min),
    max_speed(m_spd),
    current_speed(m_spd),
    maintain_speed(maintain_spd),
    environment_object(init_loc)
{
    dir = direction(rand() % 8 + 1);
    du_moved = 0;
}

mammal::mammal()
{

}

mammal::~mammal()
{
    
}

void mammal::set_direction(direction new_dir)
{
    dir = new_dir;
}

/*Name: gain_energy(int)
Purpose: generic way for mammals gain energy 
Parameters: 
    energy: int
        number of energy units to add to a mammal objects energy level
Last edit:
    BP 10/27/19
*/
void mammal::gain_energy(int added_energy)
{
    energy += added_energy;
}

void mammal::set_energy(int new_energy)
{
    energy = new_energy;
}

bool mammal::move()
{
    sim_message& message = sim_message::get_instance();
    vector<direction> untried_dirs = {up, up_right, right, down_right, down, down_left, left, up_left};
    vector<direction> untried_dirs_copy = untried_dirs;
    while(untried_dirs.size() > 0)
    {
        point move_to = location;
        switch(dir)
        {
            case up:
                move_to.y_loc++;
                break;
            case up_right:
                move_to.x_loc++;
                move_to.y_loc--;
                break;
            case right:
                move_to.x_loc++;
                break;
            case down_right:
                move_to.x_loc++;
                move_to.y_loc++;
                break;
            case down:
                move_to.y_loc++;
                break;
            case down_left:
                move_to.x_loc--;
                move_to.y_loc++;
                break;
            case left:
                move_to.x_loc--;
                break;
            case up_left:
                move_to.x_loc--;
                move_to.y_loc--;
                break;
        }
        if(message.move_organism(move_to, this))
        {
            location = move_to;
            
        }
        else
        {
            untried_dirs.erase(std::remove(untried_dirs.begin(), untried_dirs.end(), dir), untried_dirs.end());
            if(untried_dirs.size() == 0)
            {
                continue;
            }
            int dir_idx = rand() % untried_dirs.size();
            dir = untried_dirs[dir_idx];
            continue;
        }
        du_moved++;
        if(du_moved >= 5)
        {
            du_moved = 0;
            energy -= energy_output;
        }
        untried_dirs = untried_dirs_copy;
        return true;
    }
    return false;
}

void mammal::reproduce()
{

}


/*
Name: get_energy()
Purpose: return the energy of the mammal
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
Returns: energy
*/
int mammal::get_energy()
{
    return this->energy;
}


/*
Name: set_speed()
Purpose: sets a speed that is passed in to the current speed of mammal
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: max_speed
Returns: N/A
*/
void mammal::set_speed(double max_speed)
{
    this->maintain_speed = max_speed;

}
bool mammal::ready_to_reproduce()
{
    return energy >= energy_reproduce_min;
}


void mammal::set_current_speed(double speed)
{
    this->current_speed = speed;
}

/*
Name: reset_speed()
Purpose: Resets the current speed with the initial speed given
Trace: Traces to Epic 3, Acceptance Criteria 2
Parameters: N/A
Returns: N/A
*/
void mammal::reset_speed()
{
    this->current_speed = max_speed;
}

map<point, string> mammal::sight(int radius)
{
    vector<point> points_to_check;
    point p1;
    point p2;
    point p3;
    if(dir == up || dir == up_left || dir == up_right)
    {
        p1 = point(location.x_loc-150, location.y_loc-1);
        p2 = point(location.x_loc+150, location.y_loc-1);
        p3 = point(location.x_loc, location.y_loc-150);
    }
    else if(dir == left)
    {
        p1 = point(location.x_loc-1, location.y_loc-150);
        p2 = point(location.x_loc-1, location.y_loc+150);
        p3 = point(location.x_loc-150, location.y_loc);
    }
    else if(dir == right)
    {
        p1 = point(location.x_loc+1, location.y_loc-150);
        p2 = point(location.x_loc+1, location.y_loc+150);
        p3 = point(location.x_loc+150, location.y_loc);
    }
    else if(dir == down || dir == down_left || dir == down_right)
    {
        p1 = point(location.x_loc-150, location.y_loc+1);
        p2 = point(location.x_loc+150, location.y_loc+1);
        p3 = point(location.x_loc, location.y_loc+150);
    }
    points_to_check = {p1, p2, p3};
    point throwaway;
    sim_message& message = sim_message::get_instance();
    message.look_at_cell(throwaway, points_to_check);
    map<point, string> results = message.get_multiple_responses();
    return results;
}

mammal::direction mammal::find_direction(point compare)
{
    if(location.x_loc < compare.x_loc)
    {
        if(location.y_loc < compare.y_loc)
        {
            return down_right;
        }
        else if(location.y_loc > compare.y_loc)
        {
            return up_right;
        }
        else
        {
            return right;
        }
    }
    else if(location.x_loc > compare.x_loc)
    {
        if(location.y_loc < compare.y_loc)
        {
            return down_left;
        }
        else if(location.y_loc > compare.y_loc)
        {
            return up_left;
        }
        else
        {
            return left;
        }
    }
    else
    {
        if(location.y_loc < compare.y_loc)
        {
            return down;
        }
        else if(location.y_loc > compare.y_loc)
        {
            return up;
        }
    }
    //if the two locations are the same, just return up
    return up;
}

int mammal::get_energy_reproduce_min()
{
    return energy_reproduce_min;
}