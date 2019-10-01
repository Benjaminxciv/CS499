/*
Name: simulation.cpp
Purpose: Acts as the control flow for Life Simulation
Last edit: 09-29-19
Last editor: MG
*/


#include "simulation.h"

#define DATAFILE "LifeSimulation01.xml"

simulation::simulation()
{
	this->tick_speed = 1;
}

simulation::~simulation()
{

}

void simulation::set_tick_speed(int new_tick_speed)
{
	this->tick_speed = new_tick_speed;
}

void simulation::run_sim()
{
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
	grid& sim_grid = grid::get_instance(world_height,world_width);
	
	sim_grid.print_grid();

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
			cout << "Obstacle " << i << " (" << xPos << ", " << yPos << ") diameter = " << diameter << ", height = " << height << endl;
		}
		else
		{
			cout << "Failed to read data for obstacle " << i << endl;
		}
	}




/*
Purpose: test code used to prove that the virtual print_self() fx works.
Trace: Traces to Epic 2, acceptance criteria 2
*/
/*  grid& sim_grid = grid::get_instance(10,10);
    predator* plan = new predator(5,5);
    sim_grid.set_cell_contents(5, 5, plan);
    environment_object* empty_obj = sim_grid.get_cell_contents(5,5);
	for(int i=0; i< iPredatorCount; i++)
    boulder* bould = new boulder(1,1);
    sim_grid.set_cell_contents(1, 1, bould);
    environment_object* empty_obj = sim_grid.get_cell_contents(1,1);
	if(empty_obj->get_type() == "boulder")

	{
		if(empty_obj->get_type() == "predator" && empty_obj->print_self() == "*")
		{
			std::cout << "Got a predator!" << endl;
			lsdp->getPredatorData(&xPos, &yPos, &energy, genotype);
			cout << "Predator " << i << " (" << xPos << ", " << yPos << ") energy level = " << energy << ", genotype = " << genotype << endl;
			std::cout << "* : " << xPos << ", " << yPos << endl;
		}
	}
*/

    //point* p = bould2->get_loc();
    //std::cout << p->x_loc << std::endl << p->y_loc << std::endl;
    std::cin.get();
}

int main()
{

 simulation* sim = new simulation();
	sim->run_sim();
  
    return 0;
}