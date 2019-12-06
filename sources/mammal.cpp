/*Name: mammal.cpp
Purpose: Defines the structure for creating mammal objects and their functions: move ,reproduce, & gain_energy
Last edit: 12-3-19/
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
    banked_moves = 0;
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

int mammal::move()
{
    int move_count = 0;
    for (int i = 0; i < floor(banked_moves); i++)
    {
        if(try_move())
        {
            move_count++;
            banked_moves--;
        }
        else
        {
            continue;
        }
    }
    return move_count;
}

bool mammal::try_move()
{
    vector<direction> untried_dirs = {up, up_right, right, down_right, down, down_left, left, up_left};
    vector<direction> untried_dirs_copy = untried_dirs;
    while(untried_dirs.size() > 0)
    {
        sim_message& message = sim_message::get_instance();
        point move_to = location;
        switch(dir)
        {
            case up:
                //move_to.y_loc--;
                move_to.y_loc++;
                break;
            case up_right:
                move_to.x_loc++;
                //move_to.y_loc--;
                move_to.y_loc++;
                break;
            case right:
                move_to.x_loc++;
                break;
            case down_right:
                move_to.x_loc++;
                //move_to.y_loc++;
                move_to.y_loc--;
                break;
            case down:
                //move_to.y_loc++;
                move_to.y_loc--;
                break;
            case down_left:
                move_to.x_loc--;
                //move_to.y_loc++;
                move_to.y_loc--;
                break;
            case left:
                move_to.x_loc--;
                break;
            case up_left:
                move_to.x_loc--;
                //move_to.y_loc--;
                move_to.y_loc++;
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

bool mammal::restrict_sight_boulder(vector<point> boulder_locs, point obj_loc)
{
    for(int i = 0; i < boulder_locs.size(); i++)
    {
        point boulder_loc = boulder_locs[i];
        direction bould_dir = find_direction(boulder_loc);
        switch(bould_dir)
        {
            case left:
                if(obj_loc.x_loc < boulder_loc.x_loc)
                {
                    return false;
                }
                break;
            case right:
                if(obj_loc.x_loc > boulder_loc.x_loc)
                {
                    return false;
                }
                break;
            case up:
                if(obj_loc.y_loc > boulder_loc.y_loc)
                {
                    return false;
                }
                break;
            case down:
                if(obj_loc.y_loc < boulder_loc.y_loc)
                {
                    return false;
                }
                break;
            case up_left:
                if(obj_loc.x_loc <= boulder_loc.x_loc && obj_loc.y_loc >= boulder_loc.y_loc)
                {
                    return false;
                }
                break;
            case up_right:
                if(obj_loc.x_loc >= boulder_loc.x_loc && obj_loc.y_loc >= boulder_loc.y_loc)
                {
                    return false;
                }
                break;
            case down_left:
                if(obj_loc.x_loc <= boulder_loc.x_loc && obj_loc.y_loc <= boulder_loc.y_loc)
                {
                    return false;
                }
                break;
            case down_right:
                if(obj_loc.x_loc >= boulder_loc.x_loc && obj_loc.y_loc <= boulder_loc.y_loc)
                {
                    return false;
                }
                break;
        }
    }
    return true;
}

map<point, string> mammal::sight(int radius)
{
    vector<point> points_to_check;
    point p1;
    point p2;
    point p3;
    switch(dir)
    {
        case(down):
            p1 = point(location.x_loc-radius, location.y_loc-1);
            p2 = point(location.x_loc+radius, location.y_loc-1);
            p3 = point(location.x_loc, location.y_loc-radius);
            break;
        case(down_left):
            p1 = point(location.x_loc-radius, location.y_loc+(radius-1));
            p2 = point(location.x_loc+(radius-1), location.y_loc-radius);
            p3 = point(location.x_loc-radius, location.y_loc-radius);
            break;
        case(down_right):
            p1 = point(location.x_loc+radius, location.y_loc+(radius-1));
            p2 = point(location.x_loc-(radius-1), location.y_loc-radius);
            p3 = point(location.x_loc+radius, location.y_loc-radius);
            break;
        case(left):
            p1 = point(location.x_loc-1, location.y_loc-radius);
            p2 = point(location.x_loc-1, location.y_loc+radius);
            p3 = point(location.x_loc-radius, location.y_loc);
            break;
        case(right):
            p1 = point(location.x_loc+1, location.y_loc-radius);
            p2 = point(location.x_loc+1, location.y_loc+radius);
            p3 = point(location.x_loc+radius, location.y_loc);
            break;
        case(up):
            p1 = point(location.x_loc-radius, location.y_loc+1);
            p2 = point(location.x_loc+radius, location.y_loc+1);
            p3 = point(location.x_loc, location.y_loc+radius);
            break;
        case(up_left):
            p1 = point(location.x_loc-radius, location.y_loc-(radius-1));
            p2 = point(location.x_loc+(radius-1), location.y_loc+radius);
            p3 = point(location.x_loc-radius, location.y_loc+radius);
            break;
        case(up_right):
            p1 = point(location.x_loc+radius, location.y_loc-(radius-1));
            p2 = point(location.x_loc-(radius-1), location.y_loc+radius);
            p3 = point(location.x_loc+radius, location.y_loc+radius);
            break;
        default:
            p1 = point(-1,-1);

    }
    points_to_check = {p1, p2, p3};
    vision_points = points_to_check;
    sim_message& message = sim_message::get_instance();
    message.look_at_cell(location, points_to_check);
    map<point, string> results = message.get_multiple_responses();
    return results;
}

map<point, string> mammal::smell(int radius)
{
    vector<point> points_to_check;
    point p1;
    point p2;
    point p3;
    point p4;
    point p5;
    point p6;
    p1 = point(location.x_loc-radius, location.y_loc-1);
    p2 = point(location.x_loc+radius, location.y_loc-1);
    p3 = point(location.x_loc, location.y_loc-radius);

    p4 = point(location.x_loc-radius, location.y_loc);
    p5 = point(location.x_loc+radius, location.y_loc);
    p6 = point(location.x_loc, location.y_loc+radius);

    points_to_check = {p1, p2, p3, p4, p5, p6};
    sim_message& message = sim_message::get_instance();
    message.look_at_cell(location, points_to_check);
    map<point, string> results = message.get_multiple_responses();
    return results;
}

mammal::direction mammal::find_direction(point compare)
{
    if(location.x_loc < compare.x_loc)
    {
        if(location.y_loc < compare.y_loc)
        {
            return up_right;
        }
        else if(location.y_loc > compare.y_loc)
        {
            return down_right;
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
            return up_left;
        }
        else if(location.y_loc > compare.y_loc)
        {
            return down_left;
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
            return up;
        }
        else if(location.y_loc > compare.y_loc)
        {
            return down;
        }
    }
    //if the two locations are the same, just return up
    return up;
}

mammal::direction mammal::invert_dir()
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

int mammal::get_energy_reproduce_min()
{
    return energy_reproduce_min;
}

vector<point> mammal::get_vision_points()
{
    return vision_points;
}