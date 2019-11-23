
/*Name: simulation.cpp
Purpose: Runs the actual simulation, including calling all cell residents and passing their messages
Last edit: 10-22-20
Last editor: MG*/
#include <iostream>
#include "LifeSimDataParser.h"
#include "simulation.h"
#include "stdlib.h"
#include "predator.h"
#include "grazer.h"

#define DATAFILE "LifeSimulation01.xml"

simulation::simulation()
{
	this->simulation_clock = new sim_ns::clock();
	this->tick_speed = x1;
}

simulation::~simulation()
{

}

int simulation::get_world_width()
{
	return world_width;
}

int simulation::get_world_height()
{
	return world_height;
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

int simulation::get_tick_speed()
{
	return tick_speed;
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

//Put test code in here
std::vector<environment_object*> simulation::iterate_cells(bool skip_act)
{
	std::vector<environment_object*> cells;
	std::vector<point> skip_cells;
	std::vector<environment_object*> garbage_collection;
	sim_message& message = sim_message::get_instance();
	for(int x = 0; x < world_width; x++)
	{
		for(int y = 0; y < world_height; y++)
		{
			point pt(x, y);
			environment_object* cell = sim_grid->get_cell_contents(pt);
			if(cell != nullptr)
			{
				if(std::find(skip_cells.begin(), skip_cells.end(), pt) == skip_cells.end())
				{
					if(!skip_act)
					{
						cell->act();
					}
				}
				environment_object* garbage = message.get_garbage();
				if(garbage != nullptr)
				{
					delete garbage;
					message.set_garbage(nullptr);
					continue;
				}
				skip_cells.push_back(cell->get_loc());
				if(sim_grid->get_cell_contents(cell->get_loc()) != nullptr)
				{
					cells.push_back(cell);
				}
			}
		}
	}
	if(!skip_act)
	{
		simulation_clock->add_sec();
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

boulder* simulation::create_boulder(point boulder_pt, int diameter, int height)
{
	if(!sim_grid->check_bounds(boulder_pt))
	{
		return nullptr;
	}
	boulder* bold = new boulder(boulder_pt, diameter, height);
	return bold;
}

plant* simulation::create_plant(point plant_pt, int diameter)
{
	if(!sim_grid->check_bounds(plant_pt))
	{
		return nullptr;
	}
	LifeSimDataParser* lsdp = LifeSimDataParser::getInstance();
	//Plant info data
	//These values are consistent for every plant
	double plt_growth_rate = lsdp->getPlantGrowthRate();
	int plt_max_size = lsdp->getMaxPlantSize();
	int plt_max_seed_cast_dist = lsdp->getMaxSeedCastDistance();
	int plt_max_seed_num = lsdp->getMaxSeedNumber();
	double plt_seed_viability = lsdp->getSeedViability();
	int plant_diameter = diameter;
	plant* plt = new plant(plant_pt, plt_growth_rate, plt_max_size, plt_max_seed_cast_dist, plt_max_seed_num, plt_seed_viability, diameter);
	return plt;
}

leaf* simulation::create_leaf(point leaf_pt)
{
	if(!sim_grid->check_bounds(leaf_pt))
	{
		return nullptr;
	}
	leaf* lf = new leaf(leaf_pt);
	return lf;
}

seed* simulation::create_seed(point seed_pt)
{
	if(!sim_grid->check_bounds(seed_pt))
	{
		return nullptr;
	}
	seed* sd = new seed(seed_pt);
	return sd;
}

grazer* simulation::create_grazer(point grazer_pt, int init_energy)
{
	if(!sim_grid->check_bounds(grazer_pt))
	{
		return nullptr;
	}
	LifeSimDataParser* lsdp = LifeSimDataParser::getInstance();
	//Grazer info data
	//These values are consistent for every grazer
	int grz_energy_input = lsdp->getGrazerEnergyInputRate();				// Energy input per minute when grazing
	int grz_energy_output = lsdp->getGrazerEnergyOutputRate();			// Energy output when moving each 5 DU
	int grz_energy_reprod = lsdp->getGrazerEnergyToReproduce();			// Energy level needed to reproduce
	grz_energy_reprod = 800;
	double grz_max_speed = lsdp->getGrazerMaxSpeed();						// Max speed in DU per minute
	double grz_maintain_speed = lsdp->getGrazerMaintainSpeedTime();		// Minutes of simulation to maintain max speed
	grazer* grz = new grazer(grazer_pt, init_energy, grz_energy_input, grz_energy_output, grz_energy_reprod, grz_max_speed, grz_maintain_speed);
	return grz;
}

/*
Name: punnett_square
Purpose: everytime it is called, it returns the gene of one parent. If they're the same gene, it just returns the first.
         If the genes are different, it has a 50/50 percent chance of which it returns. Follows Mendel's genetics.
Trace: Traces to Epic 3, Acceptance Criteria 3
Parameters: two characters of same genotype from one predator parent.
Returns: one character of same genotype from one predator parent to pass on to the child.
*/
char pred_factory_punnett_square(char gene_one, char gene_two)
{
    if (gene_one != gene_two)
    {
        int i = rand() % 2 + 1;

        if ((i % 2) == 0)
        {
            return gene_one;
        }
        else 
        {
            return gene_two;
        }
    }
    else
    {
        return gene_one;   
    }
}

predator* simulation::create_predator(point predator_pt, int init_energy, char* genotype,
							bool is_offspring = false)
{
	if(!sim_grid->check_bounds(predator_pt))
	{
		return nullptr;
	}
	LifeSimDataParser* lsdp = LifeSimDataParser::getInstance();
	// Predator info data
	//These values are consistent for every predator
	double pred_max_speed_hod = lsdp->getPredatorMaxSpeedHOD();			// Get max speed for Homozygous Dominant FF
	double pred_max_speed_hed = lsdp->getPredatorMaxSpeedHED();			// Get max speed for Heterozygous Dominant Ff
	double pred_max_speed_hor = lsdp->getPredatorMaxSpeedHOR();			// Get max speed for Homozygous Recessive ff
	int pred_energy_output = lsdp->getPredatorEnergyOutputRate();			// Energy output when moving each 5 DU
	int pred_energy_reprod = lsdp->getPredatorEnergyToReproduce();			// Energy level needed to reproduce
	double pred_maintain_speed = lsdp->getPredatorMaintainSpeedTime();		// Minutes of simulation to maintain max speed
	int pred_max_offspring = lsdp->getPredatorMaxOffspring();				// Maximum number of offspring when reproducing
	double pred_gestation_period = lsdp->getPredatorGestationPeriod();		// Gestation period in simulation days 
	int pred_offspring_energy_level = lsdp->getPredatorOffspringEnergyLevel();		// Energy level of offspring at birth
	if(is_offspring)
	{
		init_energy = pred_offspring_energy_level;
	}
	char* genotype_trimmed = trim_lead_whitespace(genotype);
	std::string genotype_str(genotype_trimmed);
	double pred_max_speed;
	if(genotype_str[6] == 'F')
	{
		if(genotype_str[7] == 'F')
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
	
	predator* pred = new predator(predator_pt, genotype_str, init_energy, pred_energy_output, pred_energy_reprod, pred_max_speed, pred_maintain_speed,
									pred_max_speed_hod, pred_max_speed_hed, pred_max_speed_hor, pred_max_offspring,
									pred_gestation_period, pred_offspring_energy_level);
	return pred;
}

void simulation::init_sim()
{
	srand(time(NULL));
	sim_message& message = sim_message::get_instance();
	message.set_sim(this);

	LifeSimDataParser *lsdp = LifeSimDataParser::getInstance();	// Get the singleton
	lsdp->initDataParser(DATAFILE);

	simulation_clock = new sim_ns::clock();

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
			point boulder_pt(x_pos, y_pos);
			boulder* bold = create_boulder(boulder_pt, diameter, height);
			sim_grid->set_cell_contents(boulder_pt, bold);
		}
		else
		{
			//Add error checking during testing phase
		}
	}

	//Plant info data
	//for(int i = 0; i < lsdp->getInitialPlantCount(); i++)
	for(int i = 0; i < 1; i++)
	{
		int diameter;
		if(lsdp->getPlantData(&x_pos, &y_pos, &diameter))
		{
			point plant_pt(x_pos, y_pos);
			plant* plt = create_plant(plant_pt, diameter);
			sim_grid->set_cell_contents(plant_pt, plt);
		}
		else
		{
			//Add error checking during testing phase
		}
	}

	//Grazer info data
	for(int i = 0; i < lsdp->getInitialGrazerCount(); i++)
	{
		int energy;
		if(lsdp->getGrazerData(&x_pos, &y_pos, &energy))
		{
			point grazer_pt(x_pos, y_pos);
			grazer* grz = create_grazer(grazer_pt, energy);
			sim_grid->set_cell_contents(grazer_pt, grz);
		}
		else
		{
			//Add error checking during testing phase
		}
	}

	//Predator info data
	for(int i = 0; i < lsdp->getInitialPredatorCount(); i++)
	{
		int energy;
		char genotype[16];
		if(lsdp->getPredatorData(&x_pos, &y_pos, &energy, genotype))
		{
			point predator_pt(x_pos, y_pos);
			predator* pred = create_predator(predator_pt, energy, genotype);
			sim_grid->set_cell_contents(predator_pt, pred);
		}
		else
		{
			//Add error checking during testing phase
		}
	}
	//Use this for testing replacing / removing objects
	point plant_test(50,125);
	point pt = find_empty_cell(plant_test, 5);
	//seed* sd = new seed(pt);
	//grazer* gz = create_grazer(pt, 150);
	//sim_grid->set_cell_contents(pt, gz);
}

point simulation::find_empty_cell(point center, int search_radius = 1)
{
	for(int i = 1; i<search_radius; i++)
	{
		for (int x = center.x_loc-i; x < center.x_loc+i+1; x++)
		{
			point center_buf(x,center.y_loc-i);
			if(sim_grid->check_bounds(center_buf))
			{
				if(sim_grid->get_cell_contents(center_buf)== nullptr)
				{
					return center_buf;
				}
			}
			center_buf.y_loc = center.y_loc+i;
			if(sim_grid->check_bounds(center_buf))
			{
				if(sim_grid->get_cell_contents(center_buf)== nullptr)
				{
					return center_buf;
				}
			}
		}
		for (int y = center.y_loc-i+1; y < center.y_loc+i; y++)
		{
			point center_buf(center.x_loc-i, y);
			if(sim_grid->check_bounds(center_buf))
			{
				if(sim_grid->get_cell_contents(center_buf)== nullptr)
				{
					return center_buf;
				}
			}
			center_buf.x_loc = center.x_loc+i;
			if(sim_grid->check_bounds(center_buf))
			{
				if(sim_grid->get_cell_contents(center_buf)== nullptr)
				{
					return center_buf;
				}
			}
		}
	}
	return center;
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
		sim_ns::clock future_clock = *(simulation_clock);
		future_clock.add_sec(message.get_time_offset_secs());
		future_clock.add_min(message.get_time_offset_mins());
		future_clock.add_hour(message.get_time_offset_hours());
		message.set_time_info(future_clock.get_time());
		return true;
	}
	point location = message.get_location();
	if(!sim_grid->check_bounds(location))
	{
		return false;
	}
	environment_object* target_cell_contents = sim_grid->get_cell_contents(location);
	environment_object* organism = message.get_organism();
	if((organism != nullptr) && (!sim_grid->check_bounds(organism->get_loc())))
	{
		return false;
	}
	LifeSimDataParser* lsdp = LifeSimDataParser::getInstance();
	if(message.get_action_requested() == "move organism")
	{
		if(target_cell_contents == nullptr)
		{
			sim_grid->set_cell_contents(organism->get_loc(), nullptr);
			sim_grid->set_cell_contents(location, organism);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(message.get_action_requested() == "place organism")
	{
		//if(target_cell_contents == nullptr)
		//{
			int search_radius = message.get_search_radius();
			point org_pt = find_empty_cell(location, search_radius);
			if(org_pt == location)
			{
				return false;
			}
			if(message.get_environment_obj_type() == "plant")
			{
				int diameter = lsdp->getMaxPlantSize() / 10;
				organism = create_plant(message.get_location(), diameter);
			}
			else if(message.get_environment_obj_type() == "leaf")
			{
				organism = create_leaf(org_pt);
			}
			else if(message.get_environment_obj_type() == "seed")
			{
				organism = create_leaf(org_pt);
			}
			sim_grid->set_cell_contents(org_pt, organism);
			return true;
		//}
		//else
		//{
		//	return false;
		//}
	}
	else if(message.get_action_requested() == "replace organism")
	{
		if(target_cell_contents != nullptr)
		{
			message.set_garbage(target_cell_contents);
			if( message.get_environment_obj_type() == "plant")
			{
				int diameter = lsdp->getMaxPlantSize() / 10;
				organism = create_plant(message.get_location(), diameter);	
			}
			sim_grid->set_cell_contents(location, organism);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(message.get_action_requested() == "die")
	{
		message.set_garbage(organism);
		sim_grid->set_cell_contents(location, nullptr);
		return true;
	}
	//This will need to be fixed up for predators & grazers
	else if(message.get_action_requested() == "eat organism")
	{
		if(target_cell_contents != nullptr)
		{
			std::string target_type = target_cell_contents->get_type();
			if(target_type == "grazer" || target_type == "predator")
			{
				mammal* target_mammal = reinterpret_cast<mammal*>(target_cell_contents);
				message.set_organism_energy(target_mammal->get_energy());
			}
			message.set_garbage(target_cell_contents);
			sim_grid->set_cell_contents(location, nullptr);
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
		if(organism->get_type() == "grazer")
		{
			point empty_spot = find_empty_cell(location);
			if(empty_spot == location)
			{
				return false;
			}
			grazer* grz_organsim = reinterpret_cast<grazer*>(organism);
			int init_energy = grz_organsim->get_energy() / 2;
			grazer* grz = create_grazer(empty_spot, init_energy);
			sim_grid->set_cell_contents(empty_spot, grz);
			return true;
		}
		else if(organism->get_type() == "predator")
		{
			if(target_cell_contents != nullptr && target_cell_contents->get_type() == "predator")
			{
				predator* pred1 = reinterpret_cast<predator*>(organism);
				predator* pred2 = reinterpret_cast<predator*>(target_cell_contents);
				if(pred1->ready_to_reproduce() && pred2->ready_to_reproduce())
				{
					int max_offspring = pred1->get_max_offspring();
					int offspring_count = rand() % max_offspring + 1;
					for(int i = 0; i < offspring_count; i++)
					{
						point empty_spot = find_empty_cell(pred1->get_loc());
						if(empty_spot == pred1->get_loc())
						{
							continue;
						}
						std::string p1_genes = pred1->get_genotype();
						std::string p2_genes = pred2->get_genotype();
						char agr1 = pred_factory_punnett_square(p1_genes[0], p1_genes[1]);
						char agr2 = pred_factory_punnett_square(p2_genes[0], p2_genes[1]);
						char str1 = pred_factory_punnett_square(p1_genes[3], p1_genes[4]);
						char str2 = pred_factory_punnett_square(p2_genes[3], p2_genes[4]);
						char spd1 = pred_factory_punnett_square(p1_genes[6], p1_genes[7]);
						char spd2 = pred_factory_punnett_square(p2_genes[6], p2_genes[7]);
						std::string new_genotype{agr1, agr2, str1, str2, spd1, spd2};
						predator* pred = create_predator(empty_spot, 0, &new_genotype[0], true);
						sim_grid->set_cell_contents(empty_spot, pred);
					}
					return true;
				}
				else
				{
					return false;
				}	
			}
			else
			{
				return false;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}
