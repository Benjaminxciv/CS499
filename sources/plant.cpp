/*
Name: plant.cpp
Purpose: Class defining all the plant's function, such as location and growing pattern.
Last edit: 11-10-2019
Last editor: MG
*/

#include "plant.h"
#include "time.h"
#include "math.h"

plant::plant()
{

}

plant::plant(int init_x_loc, int init_y_loc) : environment_object(init_x_loc, init_y_loc)
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
    

    srand(time(0));

    int seed_pod_distance = rand() %  MAX_SEED_CAST_DISTANCE + 0;
    int seed_pod_seed_number = (rand() %  MAX_SEED_NUMBER + 0) * SEED_VIABILITY; 
}

/*
Name: radially_disperse_seeds()
Purpose: uses the viable seeds set in set_seed_pod_values() to disperse radially from the plant. 
Trace: Traces to Epic 3, acceptance criteria 1 
Parameters: N/A
Returns: N/A
*/
void plant::radially_disperse_seed()
{
    int theta = 0;
    for (int i = seed_pod_seed_number; i >= 0; i--)
    {
        int target_center_x = (cos (theta) * seed_pod_distance) + plant_x; //check maths
        int target_center_y = (sin (theta) * seed_pod_distance) + plant_y; //check maths
        theta = theta + rand() % (360/seed_pod_seed_number) + 0;
        
        sim_message& message = sim_message::get_instance();
        message.request_action("occupied", target_center_x, target_center_y);
        message.process_message();
        // check if cell is empty
        // need to check in to see if this would be correct way to test logic. 
        //if (message.request_action("occupied", target_center_x, target_center_y == false)
        
        {
            message.request_action("create new", target_center_x, target_center_y, *seed);
        }
   }
}


void plant::act()
{
    //if plant fully grown
    sim_message& message = sim_message::get_instance();
    message.get_current_time();
    message.process_message();
    time_container current_time = message.get_time_info();

    message.get_future_time(0, 0, 1);
    message.process_message();
    time_container future_time = message.get_time_info();
    
    if (current_time.time_hour == future_time.time_hour)
    {
        set_seed_pod_values();
        radially_disperse_seed();
    }
}
