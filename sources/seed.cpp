/*
Name: seed.cpp
Purpose: Class defining all the seed_pod function, such as grow timer and instantiation of plant.
Last edit: 11-10-2019
Last editor: MG
*/

#include "seed.h"

seed::seed()
{
    current_seed = nullptr;
}

seed::seed(int init_x_loc, int init_y_loc) : environment_object(init_x_loc, init_y_loc)
{
    int seed_x = init_x_loc;
    int seed_y = init_y_loc;
}

seed::~seed()
{
    
}

std::string seed::get_type()
{
    return "seed";
}

/*
Name: print_self()
Purpose: everytime it is called, it returns to environment_object this symbol.
Trace: Traces to Epic 2, acceptance criteria 2
Parameters: N/A
Returns: string with octothorpe
*/
int seed::print_self()
{
    std::cout << "s" ;

    return 0;

}

 
/*
Name: seed_grow()
Purpose: called after 10 second timer for seed_pod grows. Deletes seed pod instance and instantiates plant instead.
Trace: Traces to Epic 3, acceptance criteria 1
Parameters: N/A
Returns: N/A
*/
void seed::seed_grow()
{
    sim_message& message = sim_message::get_instance();
    plant *new_plant = new plant();
    message.request_action("delete object", seed_x, seed_y, current_seed);
    message.process_message();
    message.request_action("create new", seed_x, seed_y, new_plant);
    message.process_message();
}

void seed::act()
{
    sim_message& message = sim_message::get_instance();
    message.get_current_time();
    message.process_message();
    time_container current_time = message.get_time_info();

    message.get_future_time(10, 0, 0);
    message.process_message();
    time_container future_time = message.get_time_info();

    if (current_time.time_sec == future_time.time_sec) 
    {
      seed_grow();
    }
}