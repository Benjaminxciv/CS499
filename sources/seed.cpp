/*
Name: seed.cpp
Purpose: Class defining all the seed_pod function, such as grow timer and instantiation of plant.
Last edit: 12-3-2019
Last editor: MG
*/

#include "seed.h"


seed::seed(point loc) : environment_object(loc)
{
    retained_future_time_set = false;
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
Returns: string
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
    message.replace_organism(location, "plant");
}

void seed::act()
{
    sim_message& message = sim_message::get_instance();
    if (!retained_future_time_set)
    {
        message.get_future_time(10, 0, 0);
        retained_future_time = message.get_time_info();
        retained_future_time_set = true;
    }
    
    message.get_current_time();
    time_container current_time = message.get_time_info();

    if (current_time == retained_future_time)
    {
        seed_grow();
    }
}