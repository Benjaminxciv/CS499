
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

std::vector<environment_object*> simulation::iterate_cells()
{
	std::vector<environment_object*> cells;
	for(int x = 0; x < sim_grid->get_width(); x++)
	{
		for(int y = 0; y < sim_grid->get_height(); y++)
		{
			point pt(x, y);
			environment_object* cell = sim_grid->get_cell_contents(pt);
			if(cell != nullptr)
			{
				cell->act();
				cells.push_back(cell);
			}
		}
	}
	return cells;
}

void simulation::init_sim()
{
	sim_message& message = sim_message::get_instance();
	message.set_sim(this);

	LifeSimDataParser *lsdp = LifeSimDataParser::getInstance();	// Get the singleton
	lsdp->initDataParser(DATAFILE);

    // Call all the simple get functions and test the results
	// World info functions
	this->world_width = lsdp->getWorldWidth();
	this->world_height = lsdp->getWorldHeight();
	this->sim_grid = new grid(world_width, world_height);

	//Data parser requires references to integers to pass info
	//Every environment_object will requre an X and Y position
	//So go ahead and create those integers to be re-used
	int x_pos;
	int y_pos;

	//Obstacle info data
	for(int i = 0; i < lsdp->getObstacleCount(); i++)
	{
		int diameter;
		int height;
		if(lsdp->getObstacleData(&x_pos, &y_pos, &diameter, &height))
		{
			//cout << "Obstacle " << i << " (" << x_pos << ", " << y_pos << ") diameter = " << diameter << ", height = " << height << endl;
			point boulder_pt(x_pos, y_pos);
			boulder* bold = new boulder(boulder_pt, diameter, height);
			sim_grid->set_cell_contents(boulder_pt, bold);
		}
		else
		{
			//Add error checking during testing phase
		}
	}

	//Plant info data
	//These values are consistent for every plant
	double growth_rate = lsdp->getPlantGrowthRate();
	int max_size = lsdp->getMaxPlantSize();
	int max_seed_cast_dist = lsdp->getMaxSeedCastDistance();
	int max_seed_num = lsdp->getMaxSeedNumber();
	double seed_viability = lsdp->getSeedViability();
	for(int i = 0; i < lsdp->getInitialPlantCount(); i++)
	{
		int diameter;
		if(lsdp->getPlantData(&x_pos, &y_pos, &diameter))
		{
			point plant_pt(x_pos, y_pos);
			plant* plt = new plant(plant_pt, growth_rate, max_size, max_seed_cast_dist, max_seed_num, seed_viability);
			sim_grid->set_cell_contents(plant_pt, plt);
		}
		else
		{
			//Add error checking during testing phase
		}
	}

	//Grazer info data
	iVal = lsdp->getGrazerEnergyInputRate();				// Energy input per minute when grazing

	iVal = lsdp->getGrazerEnergyOutputRate();			// Energy output when moving each 5 DU

	iVal = lsdp->getGrazerEnergyToReproduce();			// Energy level needed to reproduce

	dVal = lsdp->getGrazerMaintainSpeedTime();		// Minutes of simulation to maintain max speed

	dVal = lsdp->getGrazerMaxSpeed();						// Max speed in DU per minute

	for(int i = 0; i < lsdp->getInitialGrazerCount(); i++)
	{
		if(lsdp->getGrazerData(&x_pos, &y_pos, &energy))
		{
			cout << "Grazer " << i << " (" << x_pos << ", " << y_pos << ") energy level = " << energy << endl;
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
		if(lsdp->getPredatorData(&x_pos, &y_pos, &energy, genotype))
		{
			cout << "Predator " << i << " (" << x_pos << ", " << y_pos << ") energy level = " << energy << ", genotype = " << genotype << endl;
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
		if(lsdp->getObstacleData(&x_pos, &y_pos, &diameter, &height))
		{
			point pt(x_pos, y_pos);
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