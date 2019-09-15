//===================================================================================
// Life Simulation Data Parser C++
// File: LifeSimDPMain.cpp
//
// Author: Dr. Rick Coleman
// Date: January 2017
//===================================================================================

#include <iostream>
#include "LifeSimDataParser.h"

using namespace std;

#define DATAFILE "LifeSimulation01.xml"

int main()
{
	int iVal;
	int iPlantCount, iGrazerCount, iPredatorCount, iObstacleCount;
	double dVal;
	int xPos, yPos;
	int diameter;
	int energy;
	char genotype[16];
	int height;


	LifeSimDataParser *lsdp = LifeSimDataParser::getInstance();	// Get the singleton
	lsdp->initDataParser(DATAFILE);

	// Call all the simple get functions and test the results
	// World info functions
	dVal = lsdp->getWorldWidth();
	cout << "World width = " << dVal;
	if(dVal == 1000.0)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	dVal = lsdp->getWorldHeight();
	cout << "World height = " << dVal;
	if(dVal == 750.0)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";


	// Plant info functions
	iVal = lsdp->getInitialPlantCount();
	cout << "Plant count = " << iVal;
	if(iVal == 25)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";
	iPlantCount = iVal;

	dVal = lsdp->getPlantGrowthRate();
	cout << "Plant growth rate = " << dVal;
	if(dVal == 0.1)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	iVal = lsdp->getMaxPlantSize();
	cout << "Plant Max Size = " << iVal;
	if(iVal == 100)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	iVal = lsdp->getMaxSeedCastDistance();
	cout << "Plant seed cast diatance = " << iVal;
	if(iVal == 250)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	iVal = lsdp->getMaxSeedNumber();
	cout << "Plant max seed number = " << iVal;
	if(iVal == 10)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	dVal = lsdp->getSeedViability();
	cout << "Plant seed viability = " << dVal;
	if(dVal == .50)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

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
	cout << "Grazer count = " << iVal;
	if(iVal == 15)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";
	iGrazerCount = iVal;

	iVal = lsdp->getGrazerEnergyInputRate();				// Energy input per minute when grazing
	cout << "Grazer energy input = " << iVal;
	if(iVal == 5)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	iVal = lsdp->getGrazerEnergyOutputRate();			// Energy output when moving each 5 DU
	cout << "Grazer energy output = " << iVal;
	if(iVal == 1)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	iVal = lsdp->getGrazerEnergyToReproduce();			// Energy level needed to reproduce
	cout << "Grazer energy to reproduce = " << iVal;
	if(iVal == 100)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	dVal = lsdp->getGrazerMaintainSpeedTime();		// Minutes of simulation to maintain max speed
	cout << "Grazer maintain speed time = " << dVal;
	if(dVal == 3.0)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	dVal = lsdp->getGrazerMaxSpeed();						// Max speed in DU per minute
	cout << "Grazer max speed = " << dVal;
	if(dVal == 20.0)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

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
	cout << "Predator count = " << iVal;
	if(iVal == 5)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";
	iPredatorCount = iVal;

	dVal = lsdp->getPredatorMaxSpeedHOD();			// Get max speed for Homozygous Dominant FF
	cout << "Predator max speed HOD = " << dVal;
	if(dVal == 20.0)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	dVal = lsdp->getPredatorMaxSpeedHED();			// Get max speed for Heterozygous Dominant Ff
	cout << "Predator max speed HED = " << dVal;
	if(dVal == 18.0)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	dVal = lsdp->getPredatorMaxSpeedHOR();			// Get max speed for Homozygous Recessive ff
	cout << "Predator max speed HOR = " << dVal;
	if(dVal == 15.0)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	iVal = lsdp->getPredatorEnergyOutputRate();			// Energy output when moving each 5 DU
	cout << "Predator energy output = " << iVal;
	if(iVal == 10)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	iVal = lsdp->getPredatorEnergyToReproduce();			// Energy level needed to reproduce
	cout << "Predator energy to reproduce = " << iVal;
	if(iVal == 500)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	dVal = lsdp->getPredatorMaintainSpeedTime();		// Minutes of simulation to maintain max speed
	cout << "Predator maintain speed time = " << dVal;
	if(dVal == 4.0)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	iVal = lsdp->getPredatorMaxOffspring();				// Maximum number of offspring when reproducing
	cout << "Predator max offspring = " << iVal;
	if(iVal == 3)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	dVal = lsdp->getPredatorGestationPeriod();		// Gestation period in simulation days 
	cout << "Predator gestation period = " << dVal;
	if(dVal == 5.0)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

	iVal = lsdp->getPredatorOffspringEnergyLevel();		// Energy level of offspring at birth
	cout << "Predator offspring energy = " << iVal;
	if(iVal == 100)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";

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
	cout << "Obstacle count = " << iVal;
	if(iVal == 15)
		cout << "\t Correct.\n";
	else
		cout << "\t Incorrect.\n";
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
	return 0;
}