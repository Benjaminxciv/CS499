
/*Name: simulation.cpp
Purpose: Runs the actual simulation, including calling all cell residents and passing their messages
Last edit: 10-22-20
Last editor: MG*/
#include <iostream>
#include "grid.h"
#include "boulder.h"
#include "LifeSimDataParser.h"
#include "plant.h"
#include "simulation.h"
#include "stdlib.h"

#define DATAFILE "LifeSimulation01.xml"

simulation::simulation()
{
	this->simulation_clock = new clock();
	this->tick_speed = 1000;
}

simulation::~simulation()
{

}

/*Name: increment_simulation_clock()
Purpose: Increment the simulation_clock by 1 tick speed.
Trace: Epic 1 Acceptance Criteria 3
Parameters: N/A
Returns: NA*/
void simulation::increment_simulation_clock()
{
	this->simulation_clock->add_sec();
}

/*Name: get_simulation_time()
Purpose: Allow access to the simulation_clock by 1 tick speed.
Trace: Epic 1 Acceptance Criteria 3
Parameters: N/A
Returns: NA*/
time_container simulation::get_simulation_time()
{
	return this->simulation_clock->get_time();
}




/*Name: set_tick_speed
Purpose: Set the refresh speed of the simulation
Trace: Epic 1 Acceptance Criteria 3
Parameters: 
	new_tick_speed: int
		The value that the tick speed will be set to
Returns: NA*/
void simulation::set_tick_speed(int new_tick_speed)
{
	this->tick_speed = new_tick_speed;
}

void simulation::increase_tick_speed()
{
	switch(this->tick_speed)
	{
		case x1:
			this->set_tick_speed(1000 / x10);
			break;
		case x10:
			this->set_tick_speed(1000 / x50);
			break;
		case x50:
			this->set_tick_speed(1000 / x100);
			break;
		case x100:
			this->set_tick_speed(1000 / x1);
			break;
		default:
			break;
	}
}

bool simulation::process_sim_message()
{
	sim_message& message = sim_message::get_instance();
	if(message.get_action_requested() == "get curr_time")
	{
		message.set_time_info(get_simulation_time());
		return true;
	}
	else if(message.get_action_requested() == "get future_time")
	{
		clock future_clock = *(simulation_clock);
		future_clock.add_sec(message.get_time_offset_secs());
		future_clock.add_min(message.get_time_offset_mins());
		future_clock.add_hour(message.get_time_offset_hours());
		message.set_time_info(future_clock.get_time());
		return true;
	}
	point location = message.get_location();
	environment_object* target_cell_contents = sim_grid->get_cell_contents(location);
	environment_object* organism = message.get_organism();
	if(message.get_action_requested() == "move organism")
	{
		if(target_cell_contents == nullptr)
		{
			sim_grid->set_cell_contents(location, organism);
			sim_grid->set_cell_contents(organism->get_loc(), nullptr);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(message.get_action_requested() == "place organism")
	{
		if(target_cell_contents == nullptr)
		{
			sim_grid->set_cell_contents(location, organism);
			return true;
		}
		else
		{
			return false;
		}
	}
	//This will need to be fixed up for predators & grazers
	else if(message.get_action_requested() == "eat organism")
	{
		if(target_cell_contents != nullptr)
		{
			delete target_cell_contents;
			sim_grid->set_cell_contents(location, nullptr);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(message.get_action_requested() == "replace organism")
	{
		if(target_cell_contents != nullptr)
		{
			delete target_cell_contents;
			sim_grid->set_cell_contents(location, organism);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(message.get_action_requested() == "look cell")
	{
		if(target_cell_contents != nullptr)
		{
			std::string cell_contents_type = target_cell_contents->get_type();
			message.set_simulation_response(cell_contents_type);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(message.get_action_requested() == "request reproduction")
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*Name: run_sim
Purpose: Runs the simulation, including reading the data file and calling all grid cells
Parameters: NA
Returns: NA*/
void simulation::run_sim()
{
	sim_message& message = sim_message::get_instance();
	message.set_sim(this);


	int iVal;
	int iPlantCount, iGrazerCount, iPredatorCount, iObstacleCount;
	double dVal;
	int xPos, yPos;
	int diameter;
	int energy;
	char genotype[16];
	int height;

	int world_height;
	int world_width;

	LifeSimDataParser *lsdp = LifeSimDataParser::getInstance();	// Get the singleton
	lsdp->initDataParser(DATAFILE);

    // Call all the simple get functions and test the results
	// World info functions
	world_height = lsdp->getWorldWidth();
	world_width = lsdp->getWorldHeight();

	sim_grid = new grid(world_width, world_height);
	
	sim_grid->print_grid();

	// Plant info functions
	iVal = lsdp->getInitialPlantCount();
	iPlantCount = iVal;

	dVal = lsdp->getPlantGrowthRate();

	iVal = lsdp->getMaxPlantSize();

	iVal = lsdp->getMaxSeedCastDistance();

	iVal = lsdp->getMaxSeedNumber();

	dVal = lsdp->getSeedViability();

	for(int i=0; i< iPlantCount; i++)
	{
		if(lsdp->getPlantData(&xPos, &yPos, &diameter))
		{
			point pt(xPos, yPos);
			plant* p = new plant(pt);
			sim_grid->set_cell_contents(pt, p);
			cout << "Plant " << i << " (" << xPos << ", " << yPos << ") diameter = " << diameter << endl;
		}
		else
		{
			cout << "Failed to read data for plant " << i << endl;
		}
	}

	// Grazer info functions
	iVal = lsdp->getInitialGrazerCount();

	iGrazerCount = iVal;

	iVal = lsdp->getGrazerEnergyInputRate();				// Energy input per minute when grazing

	iVal = lsdp->getGrazerEnergyOutputRate();			// Energy output when moving each 5 DU

	iVal = lsdp->getGrazerEnergyToReproduce();			// Energy level needed to reproduce

	dVal = lsdp->getGrazerMaintainSpeedTime();		// Minutes of simulation to maintain max speed

	dVal = lsdp->getGrazerMaxSpeed();						// Max speed in DU per minute

	for(int i=0; i< iGrazerCount; i++)
	{
		if(lsdp->getGrazerData(&xPos, &yPos, &energy))
		{
			cout << "Grazer " << i << " (" << xPos << ", " << yPos << ") energy level = " << energy << endl;
		}
		else
		{
			cout << "Failed to read data for grazer " << i << endl;
		}
	}

	// Predator info functions
	iVal = lsdp->getInitialPredatorCount();

	iPredatorCount = iVal;

	dVal = lsdp->getPredatorMaxSpeedHOD();			// Get max speed for Homozygous Dominant FF

	dVal = lsdp->getPredatorMaxSpeedHED();			// Get max speed for Heterozygous Dominant Ff

	dVal = lsdp->getPredatorMaxSpeedHOR();			// Get max speed for Homozygous Recessive ff

	iVal = lsdp->getPredatorEnergyOutputRate();			// Energy output when moving each 5 DU

	iVal = lsdp->getPredatorEnergyToReproduce();			// Energy level needed to reproduce

	dVal = lsdp->getPredatorMaintainSpeedTime();		// Minutes of simulation to maintain max speed

	iVal = lsdp->getPredatorMaxOffspring();				// Maximum number of offspring when reproducing

	dVal = lsdp->getPredatorGestationPeriod();		// Gestation period in simulation days 

	iVal = lsdp->getPredatorOffspringEnergyLevel();		// Energy level of offspring at birth

	for(int i=0; i< iPredatorCount; i++)
	{
		if(lsdp->getPredatorData(&xPos, &yPos, &energy, genotype))
		{
			cout << "Predator " << i << " (" << xPos << ", " << yPos << ") energy level = " << energy << ", genotype = " << genotype << endl;
		}
		else
		{
			cout << "Failed to read data for predator " << i << endl;
		}
	}

	// Obstacle info data
	iVal = lsdp->getObstacleCount();						// Number of obstacles

	iObstacleCount = iVal;

	for(int i=0; i< iObstacleCount; i++)
	{
		if(lsdp->getObstacleData(&xPos, &yPos, &diameter, &height))
		{
			point pt(xPos, yPos);
			boulder* b = new boulder(pt, diameter, height);
		}
		else
		{
			cout << "Failed to read data for obstacle " << i << endl;
		}
	}

  
	while(1)
	{
    	for(int x = 0; x < world_width; x++)
		{
			for(int y = 0; y < world_height; y++)
			{
				point pt(x, y);
				environment_object* actor = sim_grid->get_cell_contents(pt);
				if(actor != nullptr)
				{
					actor->act();
				}
			}
		}
		_sleep(this->tick_speed);
	}

    std::cin.get();
}

int main()
{

 	simulation* sim = new simulation();
	sim->run_sim();
  
    return 0;
}
