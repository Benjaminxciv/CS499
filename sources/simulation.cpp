
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


//Helper function for stripping leading whitespace from string
char* trim_lead_whitespace(char* str)
{
    int str_idx = 0; // number of leading spaces
	while(str[str_idx] != '\0' && (str[str_idx] == ' ' || str[str_idx++] == '\t'));
	return str+str_idx-1;
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
	double plt_growth_rate = lsdp->getPlantGrowthRate();
	int plt_max_size = lsdp->getMaxPlantSize();
	int plt_max_seed_cast_dist = lsdp->getMaxSeedCastDistance();
	int plt_max_seed_num = lsdp->getMaxSeedNumber();
	double plt_seed_viability = lsdp->getSeedViability();
	for(int i = 0; i < lsdp->getInitialPlantCount(); i++)
	{
		int diameter;
		if(lsdp->getPlantData(&x_pos, &y_pos, &diameter))
		{
			point plant_pt(x_pos, y_pos);
			plant* plt = new plant(plant_pt, plt_growth_rate, plt_max_size, plt_max_seed_cast_dist, plt_max_seed_num, plt_seed_viability);
			sim_grid->set_cell_contents(plant_pt, plt);
		}
		else
		{
			//Add error checking during testing phase
		}
	}

	//Grazer info data
	int grz_energy_input = lsdp->getGrazerEnergyInputRate();				// Energy input per minute when grazing
	int grz_energy_output = lsdp->getGrazerEnergyOutputRate();			// Energy output when moving each 5 DU
	int grz_energy_reprod = lsdp->getGrazerEnergyToReproduce();			// Energy level needed to reproduce
	double grz_max_speed = lsdp->getGrazerMaxSpeed();						// Max speed in DU per minute
	double grz_maintain_speed = lsdp->getGrazerMaintainSpeedTime();		// Minutes of simulation to maintain max speed
	for(int i = 0; i < lsdp->getInitialGrazerCount(); i++)
	{
		int energy;
		if(lsdp->getGrazerData(&x_pos, &y_pos, &energy))
		{
			point grazer_pt(x_pos, y_pos);
			grazer* grz = new grazer(grazer_pt, energy, grz_energy_input, grz_energy_output, grz_energy_reprod, grz_max_speed, grz_maintain_speed);
			sim_grid->set_cell_contents(grazer_pt, grz);
		}
		else
		{
			//Add error checking during testing phase
		}
	}

	// Predator info functions
	double pred_max_speed_hod = lsdp->getPredatorMaxSpeedHOD();			// Get max speed for Homozygous Dominant FF
	double pred_max_speed_hed = lsdp->getPredatorMaxSpeedHED();			// Get max speed for Heterozygous Dominant Ff
	double pred_max_speed_hor = lsdp->getPredatorMaxSpeedHOR();			// Get max speed for Homozygous Recessive ff
	int pred_energy_output = lsdp->getPredatorEnergyOutputRate();			// Energy output when moving each 5 DU
	int pred_energy_reprod = lsdp->getPredatorEnergyToReproduce();			// Energy level needed to reproduce
	double pred_maintain_speed = lsdp->getPredatorMaintainSpeedTime();		// Minutes of simulation to maintain max speed
	int pred_max_offspring = lsdp->getPredatorMaxOffspring();				// Maximum number of offspring when reproducing
	double pred_gestation_period = lsdp->getPredatorGestationPeriod();		// Gestation period in simulation days 
	int pred_offspring_energy_level = lsdp->getPredatorOffspringEnergyLevel();		// Energy level of offspring at birth

//point init_loc, int init_e, int e_output, int e_reprod_min, double m_spd, double maintain_spd,
//                    double m_spd_hod, double m_spd_hed, double m_spd_hor, int m_offsprg, int gest_prd, int offsprg_e_lvl

	for(int i = 0; i < lsdp->getInitialPredatorCount(); i++)
	{
		int energy;
		char genotype[16];
		if(lsdp->getPredatorData(&x_pos, &y_pos, &energy, genotype))
		{
			char* genotype_trimmed = trim_lead_whitespace(genotype);
			point predator_pt(x_pos, y_pos);
			double pred_max_speed;
			if(genotype[6] == 'F')
			{
				if(genotype[7] == 'F')
				{
					pred_max_speed = pred_max_speed_hod;
				}
				else
				{
					pred_max_speed = pred_max_speed_hed;
				}
			}
			else
			{
				pred_max_speed = pred_max_speed_hor;
			}
			
			predator* pred = new predator(predator_pt, energy, pred_energy_output, pred_energy_reprod, pred_max_speed, pred_maintain_speed,
											pred_max_speed_hod, pred_max_speed_hed, pred_max_speed_hor, pred_max_offspring,
											pred_gestation_period, pred_offspring_energy_level);
			sim_grid->set_cell_contents(predator_pt, pred);
		}
		else
		{
			//Add error checking during testing phase
		}
	}

	// Obstacle info data

	for(int i = 0; i < lsdp->getObstacleCount(); i++)
	{
		int diameter;
		int height;
		if(lsdp->getObstacleData(&x_pos, &y_pos, &diameter, &height))
		{
			point boulder_pt(x_pos, y_pos);
			boulder* bld = new boulder(boulder_pt, diameter, height);
			sim_grid->set_cell_contents(boulder_pt, bld);
		}
		else
		{
			//Add error checking during testing phase
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