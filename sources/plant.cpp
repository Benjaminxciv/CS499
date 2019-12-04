/*
Name: plant.cpp
Purpose: Class defining all the plant's function, such as location and growing pattern.
Last edit: 12-3-2019
Last editor: MG
*/

#include "plant.h"
#include "time.h"
#include "math.h"


plant::plant(point init_loc, double grow_rate, int m_size, int m_seed_dist, int max_seed, double seed_via, int init_plant_size) : 
    growth_rate(grow_rate),
    max_size(m_size),
    max_seed_cast_dist(m_seed_dist),
    max_seed_num(max_seed),
    seed_viability(seed_via),
    environment_object(init_loc),
    initial_plant_size(init_plant_size)
    
{
    retained_future_time_set = false;
    current_size = 0;
}

plant::~plant()
{
    
}

std::string plant::get_type()
{
    return "plant";
}

/*
Name: print_self()
Purpose: everytime it is called, it returns to environment_object this symbol.
Trace: Traces to Epic 2, acceptance criteria 2
Parameters: N/A
Returns: string with octothorpe
*/
int plant::print_self()
{
    std::cout << "#" ;

    return 0;

}

 int plant::get_current_size()
 {
     return current_size;
 }

 int plant::get_max_size()
 {
     return max_size;
 }

/*
Name: growth()
Purpose: Calcualtes the number of leaves that can be placed in one simulation tick. 
Trace: Traces to Epic 3, acceptance criteria 1
Parameters: N/A
Returns: N/A
*/
void plant::grow()
{
    int num_total_leaves = max_size - current_size;
    int num_leaves_possible_in_tick = num_total_leaves * growth_rate;

    for (int z = num_leaves_possible_in_tick; z >= 0; z--)
    {
        sim_message& message = sim_message::get_instance();
        if(message.place_organism( location, "leaf", id, (max_size/2)))
        {
            
        }
    }
}

/*
Name: seed_pod_values()
Purpose: everytime it is called, sets the randomized numbers for seed pod traits. 
Trace: Traces to Epic 3, acceptance criteria 1 
Parameters: N/A
Returns: N/A
*/
void plant::set_seed_pod_values()
{
    int seed_pod_distance = rand() %  max_seed_cast_dist + 0;
    int seed_pod_seed_number = (rand() %  max_seed_num + 0) * seed_viability; 
}

/*
Name: radially_disperse_seeds()
Purpose: uses the viable seeds set in set_seed_pod_values() to disperse radially from the plant. 
        1 collision resolution. If it fails to place seed after 1 time, it loses that seed. 
Trace: Traces to Epic 3, acceptance criteria 1 
Parameters: N/A
Returns: N/A
*/
void plant::radially_disperse_seed()
{
    int theta = 0;
    for (int i = max_seed_num; i >= 0; i--)
    {
        int target_center_x = (cos (theta) * max_seed_cast_dist) + location.x_loc;
        int target_center_y = (sin (theta) * max_seed_cast_dist) + location.y_loc;
        point pt(target_center_x, target_center_y);
        theta = theta + rand() % (360/max_seed_num) + 0;
        
        sim_message& message = sim_message::get_instance();
        if(!message.place_organism(pt, "seed", id))
        {
            target_center_x = (cos (theta) * max_seed_cast_dist) + location.x_loc;
            target_center_y = (sin (theta) * max_seed_cast_dist) + location.y_loc;
            point pt2(target_center_x,target_center_y);
            theta = theta + rand() % (360/41) + 0;
            message.place_organism(pt2, "seed", id);
        }
   }
}


void plant::act()
{
    sim_message& message = sim_message::get_instance();
    message.request_child_list(id);
    current_size = message.get_child_list().size();
    if (current_size >= max_size)
    {
        message.get_current_time();
        time_container current_time = message.get_time_info();

        if (!retained_future_time_set)
        {
            message.get_future_time(0, 0, 1);
            retained_future_time = message.get_time_info();
            retained_future_time_set = true;
        }
        
        if (current_time == retained_future_time)
        {
            retained_future_time_set = false;
            set_seed_pod_values();
            radially_disperse_seed();
        }
    }
    else
    {
        grow();
    }
}
