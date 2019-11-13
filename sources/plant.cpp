/*
Name: plant.cpp
Purpose: Class defining all the plant's function, such as location and growing pattern.
Last edit: 11-12-2019
Last editor: MG
*/

#include "plant.h"
#include "time.h"
#include "math.h"

plant::plant()
{

}

plant::plant(point init_loc) : environment_object(init_loc)
{
    int plant_x = init_x_loc;
    int plant_y = init_y_loc;
    LifeSimDataParser *gather = NULL;


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


/*
Name: seed_pod_values()
Purpose: everytime it is called, sets the randomized numbers for seed pod traits. 
Trace: Traces to Epic 3, acceptance criteria 1 
Parameters: N/A
Returns: N/A
*/
void plant::set_seed_pod_values()
{
    //does not read from file every time. One read is done at the beginning in LifeSimDataParser
    // thus, it is returned from local variable. it's a singleton instance.
    int MAX_SEED_CAST_DISTANCE = info_gather ->getMaxSeedCastDistance() ;
    int MAX_SEED_NUMBER = info_gather->getMaxSeedNumber();
    double SEED_VIABILITY = info_gather->getSeedViability();

    int seed_pod_distance = rand() %  MAX_SEED_CAST_DISTANCE + 0;
    int seed_pod_seed_number = (rand() %  MAX_SEED_NUMBER + 0) * SEED_VIABILITY; 
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
    for (int i = seed_pod_seed_number; i >= 0; i--)
    {
        int target_center_x = (cos (theta) * seed_pod_distance) + plant_x;
        int target_center_y = (sin (theta) * seed_pod_distance) + plant_y;
        point pt(target_center_x, target_center_y);
        theta = theta + rand() % (360/seed_pod_seed_number) + 0;
        
        sim_message& message = sim_message::get_instance();
        if(!message.place_organism(pt, *seed))
        {
            target_center_x = (cos (theta) * seed_pod_distance) + plant_x;
            target_center_y = (sin (theta) * seed_pod_distance) + plant_y;
            point pt2(target_center_x,target_center_y;)
            theta = theta + rand() % (360/41) + 0;
            message.place_organism(pt2, *seed);
        }
   }
}


void plant::act()
{
    //TODO:: add if check for plant fully grown
    sim_message& message = sim_message::get_instance();
    message.get_current_time();
    time_container current_time = message.get_time_info();

    message.get_future_time(0, 0, 1);
    time_container future_time = message.get_time_info();
    
    if (current_time.time_hour == future_time.time_hour)
    {
        set_seed_pod_values();
        radially_disperse_seed();
    }
}
