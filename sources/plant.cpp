/*
Name: plant.cpp
Purpose: Class defining all the plant's function, such as location and growing pattern.
Last edit: 09-29-2019
Last editor: AW
*/

#include "plant.h"
#include "time.h"
#include "clock.h"

plant::plant(point init_loc) : environment_object(init_loc)
{

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
void set_seed_pod_values()
{

    //used for testing purposes only - these values will be provided by the XML file.
    int MAX_SEED_CAST_DISTANCE = 100;
    int MAX_SEED_NUMBER = 50;
    

    srand(time(0));

    int seed_pod_distance = rand() %  MAX_SEED_CAST_DISTANCE + 0;
    int seed_pod_seed_number = rand() %  MAX_SEED_NUMBER + 0; 

    std::cout << "seed pod distance: " << seed_pod_distance;
    std::cout << "\nseed pod number: " << seed_pod_seed_number;

}

/*
Name: seed()
Purpose: accounts for attributes of the plant's seeds. Viability, begin growth, and rate of growth.
Trace: Traces to Epic 3, acceptance criteria 1 
Parameters: N/A
Returns: N/A
*/
void seed_grow()
{
    
}

void plant::act()
{
    sim_message& message = sim_message::get_instance();
    message.get_current_time();
    message.process_message();
    time_container timer = message.get_time_info();
    std::cout << timer.time_sec << std::endl;

    message.get_future_time(10);
    message.process_message();
    time_container timer2 = message.get_time_info();
    std::cout << timer2.time_sec << std::endl;
}