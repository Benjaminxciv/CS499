//===================================================================================
// Life Simulation Data Parser C++
// File: LifeSimDataParser.h
//
// Author: Dr. Rick Coleman
// Date: January 2017
//===================================================================================
#ifndef LIFESIMDATAPARSER_H
#define LIFESIMDATAPARSER_H

#include <fstream>

using namespace std;

class LifeSimDataParser
{
	private:
		char m_sFileName[64];
		ifstream	*inFile;	     // Life Sim world definition file

		// Map data
		double m_dWorldWidth;
		double m_dWorldHeight;
		// Plant data
		int m_iNumPlants;
		int m_iPlantCount;
		double m_dPlantGrowthRate;
		int m_iMaxPlantSize;
		int m_iMaxSeedCast;
		int m_iMaxSeedNumber;
		double m_dSeedViability;
		// Grazer data
		int m_iNumGrazers;
		int m_iGrazerCount;
		int m_iGEInputRate;
		int m_iGEOutputRate;
		int m_iGEReproduce;
		double m_dGMaintainSpeed;
		double m_dGMaxSpeed;
		// Predator data
		int m_iNumPredators;
		int m_iPredatorCount;
		double m_dMaxSpeedHOD;
		double m_dMaxSpeedHED;
		double m_dMaxSpeedHOR;
		int m_iPEOutputRate;
		int m_iPEReproduce;
		double m_dPMaintainSpeed;
		int m_iPMaxOffspring;
		double m_dPGestation;
		int m_iPOffspringEnergy;

		// Obstacle data
		int m_iNumObstacles;
		int m_iObstacleCount;

		LifeSimDataParser();						// Default constructor for singleton
		bool getNextLine(char *buffer, int n);		// Read a line from the data file

	public:
		static LifeSimDataParser *getInstance();			// Get the singleton instance of this class
		~LifeSimDataParser();						// Destructor
		void initDataParser(char *filename);		// Initiaize the data parser with data file name
		// World info functions
		double getWorldWidth();
		double getWorldHeight();

		// Plant info functions
		int getInitialPlantCount();
		double getPlantGrowthRate();
		int getMaxPlantSize();
		int getMaxSeedCastDistance();
		int getMaxSeedNumber();
		double getSeedViability();
		bool getPlantData(int *X, int *Y, int *diameter);

		// Grazer info functions
		int getInitialGrazerCount();
		int getGrazerEnergyInputRate();				// Energy input per minute when grazing
		int getGrazerEnergyOutputRate();			// Energy output when moving each 5 DU
		int getGrazerEnergyToReproduce();			// Energy level needed to reproduce
		double getGrazerMaintainSpeedTime();		// Minutes of simulation to maintain max speed
		double getGrazerMaxSpeed();						// Max speed in DU per minute
		bool getGrazerData(int *X, int *Y, int *energy);

		// Predator info functions
		int getInitialPredatorCount();
		double getPredatorMaxSpeedHOD();			// Get max speed for Homozygous Dominant FF
		double getPredatorMaxSpeedHED();			// Get max speed for Heterozygous Dominant Ff
		double getPredatorMaxSpeedHOR();			// Get max speed for Homozygous Recessive ff
		int getPredatorEnergyOutputRate();			// Energy output when moving each 5 DU
		int getPredatorEnergyToReproduce();			// Energy level needed to reproduce
		double getPredatorMaintainSpeedTime();		// Minutes of simulation to maintain max speed
		int getPredatorMaxOffspring();				// Maximum number of offspring when reproducing
		double getPredatorGestationPeriod();		// Gestation period in simulation days 
		int getPredatorOffspringEnergyLevel();		// Energy level of offspring at birth
		bool getPredatorData(int *X, int *Y, int *energy, char *gen);

		// Obstacle info data
		int getObstacleCount();						// Number of obstacles
		bool getObstacleData(int *X, int *Y, int *diameter, int *height);
};

#endif