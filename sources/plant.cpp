/*
Name: plant.cpp
Purpose: Contains all the information specific to plant lifeforms for Life Simulation.
Last edit: 09-25-19
Last editor: MG
*/

#include "plant.h"
#include "time.h"

plant::plant(int init_x_loc, int init_y_loc) : environment_object(init_x_loc, init_y_loc)
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
Name: seed_pod_values()
Purpose: everytime it is called, sets the randomized numbers for seed pod traits. 
Trace: Traces to Epic 3, acceptance criteria 1 
Parameters: N/A
Returns: N/A
*/
void seed_pod_values()
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




