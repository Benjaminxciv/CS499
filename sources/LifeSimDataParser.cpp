//===================================================================================
// Life Simulation Data Parser C++
// File: LifeSimDataParser.cpp
//
// Author: Dr. Rick Coleman
// Date: January 2017
//===================================================================================
#include <string>
#include <iostream>
#include "LifeSimDataParser.h"

using namespace std;

//------------------------------------------
// Default constructor
//------------------------------------------
LifeSimDataParser::LifeSimDataParser()
{
	// Map data
	m_dWorldWidth = 0.0;
	m_dWorldHeight = 0.0;
	// Plant data
	m_iNumPlants = 0;
	m_iPlantCount = 0;
	m_dPlantGrowthRate = 0.0;
	m_iMaxPlantSize = 0;
	m_iMaxSeedCast = 0;
	m_iMaxSeedNumber = 0;
	m_dSeedViability = 0.0;
	// Grazer data
	m_iNumGrazers = 0;
	m_iGrazerCount = 0;
	m_iGEInputRate = 0;
	m_iGEOutputRate = 0;
	m_iGEReproduce = 0;
	m_dGMaintainSpeed = 0.0;
	m_dGMaxSpeed = 0.0;
	// Predator data
	m_iNumPredators = 0;
	m_iPredatorCount = 0;
	m_dMaxSpeedHOD = 0.0;
	m_dMaxSpeedHED = 0.0;
	m_dMaxSpeedHOR = 0.0;
	m_iPEOutputRate = 0;
	m_iPEReproduce = 0;
	m_dPMaintainSpeed = 0.0;
	m_iPMaxOffspring = 0;
	m_dPGestation = 0.0;
	m_iPOffspringEnergy = 0;
	// Obstacle data
	m_iNumObstacles = 0;
	m_iObstacleCount = 0;
}

//------------------------------------------
// Destructor
//------------------------------------------
LifeSimDataParser::~LifeSimDataParser()
{
}

//------------------------------------------
// Get the singleton instance of this class
//------------------------------------------
LifeSimDataParser *LifeSimDataParser::getInstance()
{
	static LifeSimDataParser *theInstance = NULL;
	if(theInstance == NULL)
	{
		theInstance = new LifeSimDataParser();
	}
	return theInstance;
}

//------------------------------------------
// Initiaize the data parser with data file name
//------------------------------------------
void LifeSimDataParser::initDataParser(char *filename)
{
	char line[128];

	strcpy(m_sFileName, filename);		// Save the file name
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in); // Open the data file

	if(inFile->is_open())
	{
		// Get the basic information
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<WIDTH>") == 0)
			{
				getNextLine(line, 127); // Get map width
				m_dWorldWidth = atof(line);
			}
			else if(strcmp(line, "<HEIGHT>") == 0)
			{
				getNextLine(line, 127); // Get map height
				m_dWorldHeight = atof(line);
			}
			else if(strcmp(line, "<INITIAL_PLANT_COUNT>") == 0)
			{
				getNextLine(line, 127); 
				m_iNumPlants = atoi(line); // Get plant count
			}
			else if(strcmp(line, "<GROWTH_RATE>") == 0)
			{
				getNextLine(line, 127); // Get plant growth rate
				m_dPlantGrowthRate = atof(line);
			}
			else if(strcmp(line, "<MAX_SIZE>") == 0)
			{
				getNextLine(line, 127); // Get plant max size
				m_iMaxPlantSize = atoi(line);
			}
			else if(strcmp(line, "<MAX_SEED_CAST_DISTANCE>") == 0)
			{
				getNextLine(line, 127); // Get plant max size
				m_iMaxSeedCast = atoi(line);
			}
			else if(strcmp(line, "<MAX_SEED_NUMBER>") == 0)
			{
				getNextLine(line, 127); // Get max number of seeds a plant can produce
				m_iMaxSeedNumber = atoi(line);
			}
			else if(strcmp(line, "<SEED_VIABILITY>") == 0)
			{
				getNextLine(line, 127); // Get seed viability percentage
				m_dSeedViability = atof(line);
			}
			else if(strcmp(line, "<INITIAL_GRAZER_COUNT>") == 0)
			{
				getNextLine(line, 127); // Get number of grazers
				m_iNumGrazers = atoi(line);
			}
			else if(strcmp(line, "<G_ENERGY_INPUT>") == 0)
			{
				getNextLine(line, 127); // Get grazer energy obtained when eating
				m_iGEInputRate = atoi(line);
			}
			else if(strcmp(line, "<G_ENERGY_OUTPUT>") == 0)
			{
				getNextLine(line, 127); // Get grazer energy output when moving
				m_iGEOutputRate = atoi(line);
			}
			else if(strcmp(line, "<G_ENERGY_TO_REPRODUCE>") == 0)
			{
				getNextLine(line, 127); // Get grazer energy to reproduce
				m_iGEReproduce = atoi(line);
			}
			else if(strcmp(line, "<G_MAINTAIN_SPEED>") == 0)
			{
				getNextLine(line, 127); // Get grazer time to maintain speed
				m_dGMaintainSpeed = atof(line);
			}
			else if(strcmp(line, "<G_MAX_SPEED>") == 0)
			{
				getNextLine(line, 127); // Get grazer max speed
				m_dGMaxSpeed = atof(line);
			}
			else if(strcmp(line, "<INITIAL_PREDATOR_COUNT>") == 0)
			{
				getNextLine(line, 127); // Get initial predator count
				m_iNumPredators = atoi(line);
			}
			else if(strcmp(line, "<MAX_SPEED_HOD>") == 0)
			{
				getNextLine(line, 127); // Get predator max speed when homozygous dominant FF
				m_dMaxSpeedHOD = atof(line);
			}
			else if(strcmp(line, "<MAX_SPEED_HED>") == 0)
			{
				getNextLine(line, 127); // Get predator max speed when heterozygous dominant Ff
				m_dMaxSpeedHED = atof(line);
			}
			else if(strcmp(line, "<MAX_SPEED_HOR>") == 0)
			{
				getNextLine(line, 127); // Get predator max speed when homozygous recessive ff
				m_dMaxSpeedHOR = atof(line);
			}
			else if(strcmp(line, "<P_ENERGY_OUTPUT>") == 0)
			{
				getNextLine(line, 127); // Get predator energy output when moving
				m_iPEOutputRate = atoi(line);
			}
			else if(strcmp(line, "<P_MAINTAIN_SPEED>") == 0)
			{
				getNextLine(line, 127); // Get predator time to maintain speed
				m_dPMaintainSpeed = atof(line);
			}
			else if(strcmp(line, "<P_ENERGY_TO_REPRODUCE>") == 0)
			{
				getNextLine(line, 127); // Get predator energy to reproduce
				m_iPEReproduce = atoi(line);
			}
			else if(strcmp(line, "<P_MAX_OFFSPRING>") == 0)
			{
				getNextLine(line, 127); // Get predator max offspring count
				m_iPMaxOffspring = atoi(line);
			}
			else if(strcmp(line, "<P_GESTATION>") == 0)
			{
				getNextLine(line, 127); // Get predator gestation time
				m_dPGestation = atof(line);
			}
			else if(strcmp(line, "<P_OFFSPRING_ENERGY>") == 0)
			{
				getNextLine(line, 127); // Get predator offspring level at birth
				m_iPOffspringEnergy = atoi(line);
			}
			else if(strcmp(line, "<INITIAL_OBSTACLE_COUNT>") == 0)
			{
				getNextLine(line, 127); // Get initial obstacle count
				m_iNumObstacles = atoi(line);
			}
		}
		inFile->close();
	}
	else
	{
		cout << "***** FAILED TO OPEN THE DATA FILE *****" << endl;
		cout << "You will not be able to read simulation data.\n";
	}
}

//------------------------------------------
// Get the map width in Distance Units (DU)
//------------------------------------------
double LifeSimDataParser::getWorldWidth()
{
	return m_dWorldWidth;
}

//------------------------------------------
// Get the map height in Distance Units (DU)
//------------------------------------------
double LifeSimDataParser::getWorldHeight()
{
	return m_dWorldHeight;
}

//------------------------------------------
// Get the initial number of plants
//------------------------------------------
int LifeSimDataParser::getInitialPlantCount()
{
	return m_iNumPlants;
}

//----------------------------------------------
// Get plant growth rate in Distance Units (DU)
//----------------------------------------------
double LifeSimDataParser::getPlantGrowthRate()
{
	return m_dPlantGrowthRate;
}

//------------------------------------------
// Get max seed casting distance when a plant
// produces seeds, in Distance Units (DU)
//------------------------------------------
int LifeSimDataParser::getMaxSeedCastDistance()
{
	return m_iMaxSeedCast;
}

//------------------------------------------
// Get max plant size in Distance Units (DU)
//------------------------------------------
int LifeSimDataParser::getMaxPlantSize()
{
	return m_iMaxPlantSize;
}

//----------------------------------------------
// Get max number of seeds a plant can produce.
//----------------------------------------------
int LifeSimDataParser::getMaxSeedNumber()
{
	return m_iMaxSeedNumber;
}

//------------------------------------------
// Get seed viability as percent of seeds
//	a plant produces that will germinate
//	and grow.
//------------------------------------------
double LifeSimDataParser::getSeedViability()
{
	return m_dSeedViability;
}

//-------------------------------------------------------------------
// Get all the data on a single plant
// Args:
//		X - pointer to int variable to hold X coordinate mid-point
//		Y - pointer to int variable to hold Y coordinate mid-point
//		dia - pointer to int variable to hold plant
//					diameter at start of simulation
//		All measures are in Distance Units (DU)
// Returns: true as long as there was another plant to read.
//			false when all plants have been read.
//-------------------------------------------------------------------
bool LifeSimDataParser::getPlantData(int *X, int *Y, int *dia)
{
	int dNum = 0;
	char line[128];
	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		// Read to the the current Plant count
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<PLANT>") == 0) // Got one
			{
				if(dNum == m_iPlantCount)
				{
					// Get data on this one
					while(getNextLine(line, 127))
					{
						// Get the X position
						if(strcmp(line, "<X_POS>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*X = atoi(line); // Set the X position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<Y_POS>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*Y = atoi(line); // Set the Y position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<P_DIAMETER>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*dia = atoi(line); // Set the radius
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "</PLANT>") == 0)
						{
							m_iPlantCount++; // Increment for next call to this function
							return true; // Got it
						}
					} // end while
				} // end if(dNum == m_iPlantCount)
				else
				{
					dNum++; // Check the next one
				}
			}
		}
		inFile->close();
	} // end if file open
	return false; // If we get here we have got all the Plants
}

//------------------------------------------
// Get initial number of grazers
//------------------------------------------
int LifeSimDataParser::getInitialGrazerCount()
{
	return m_iNumGrazers;
}

//--------------------------------------------
// Get the energy input per simulation minute 
//	when a grazer is grazing
//--------------------------------------------
int LifeSimDataParser::getGrazerEnergyInputRate()
{
	return m_iGEInputRate;
}

//---------------------------------------------
// Get the energy output when a grazer is
//	moving.  This is amount of energy expended
//	for each 5 Distance Units (DU) moved.
//---------------------------------------------
int LifeSimDataParser::getGrazerEnergyOutputRate()
{
	return m_iGEOutputRate;
}

//---------------------------------------------------
// Get the energy level a grazer needs to reproduce
//---------------------------------------------------
int LifeSimDataParser::getGrazerEnergyToReproduce()
{
	return m_iGEReproduce;
}

//----------------------------------------------
// Get the minutes of simulation time a grazer
//	can maintain its' max speed when fleeing
//	a predator
//----------------------------------------------
double LifeSimDataParser::getGrazerMaintainSpeedTime()
{
	return m_dGMaintainSpeed;
}

//------------------------------------------
// Get the max speed in Distance Units (DU)
//	per minute a grazer can run.
//------------------------------------------
double LifeSimDataParser::getGrazerMaxSpeed()
{
	return m_dGMaxSpeed;
}

//-------------------------------------------------------------
// Get all the data on a single grazer
// Args:
//		X - pointer to int variable to hold X coordinate
//		Y - pointer to int variable to hold Y coordinate
//		energy - pointer to double variable to hold grazer
//					energy at start of simulation
// Returns: true as long as there was another grazer to read.
//			false when all grazers have been read.
//-------------------------------------------------------------
bool LifeSimDataParser::getGrazerData(int *X, int *Y, int *energy)
{
	int dNum = 0;
	char line[128];
	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		// Read to the the current Grazer count
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<GRAZER>") == 0) // Got one
			{
				if(dNum == m_iGrazerCount)
				{
					// Get data on this one
					while(getNextLine(line, 127))
					{
						// Get the X position
						if(strcmp(line, "<X_POS>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*X = atoi(line); // Set the X position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<Y_POS>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*Y = atoi(line); // Set the Y position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<G_ENERGY_LEVEL>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*energy = atoi(line); // Set the energy level
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "</GRAZER>") == 0)
						{
							m_iGrazerCount++; // Increment for next call to this function
							return true; // Got it
						}
					} // end while
				} // end if(dNum == m_iGrazerCount)
				else
				{
					dNum++; // Check the next one
				}
			}
		}
		inFile->close();
	} // end if file open
	return false; // If we get here we have got all the grazers
}

//------------------------------------------
// Get initial number of predators
//------------------------------------------
int LifeSimDataParser::getInitialPredatorCount()
{
	return m_iNumPredators;
}

//-----------------------------------------------
// Get max speed of a predator with homozygous
//	dominant genotype for speed of FF
//-----------------------------------------------
double LifeSimDataParser::getPredatorMaxSpeedHOD()
{
	return m_dMaxSpeedHOD;
}

//-----------------------------------------------
// Get max speed of a predator with heterozygous
//	dominent genotype for speed of Ff
//-----------------------------------------------
double LifeSimDataParser::getPredatorMaxSpeedHED()
{
	return m_dMaxSpeedHED;
}

//-----------------------------------------------
// Get max speed of a predator with homozygous
//	recessive genotype for speed of ff
//-----------------------------------------------
double LifeSimDataParser::getPredatorMaxSpeedHOR()
{
	return m_dMaxSpeedHOR;
}

//---------------------------------------------
// Get the energy output when a predator is
//	moving.  This is amount of energy expended
//	for each 5 Distance Units (DU) moved.
//---------------------------------------------
int LifeSimDataParser::getPredatorEnergyOutputRate()
{
	return m_iPEOutputRate;
}

//-----------------------------------------------------
// Get the energy level a predator needs to reproduce
//-----------------------------------------------------
int LifeSimDataParser::getPredatorEnergyToReproduce()
{
	return m_iPEReproduce;
}

//----------------------------------------------
// Get the minutes of simulation time a predator
//	can maintain its' max speed when pursuing
//	a grazer
//----------------------------------------------
double LifeSimDataParser::getPredatorMaintainSpeedTime()
{
	return m_dPMaintainSpeed;
}

//---------------------------------------------------
// Get maximum number of offspring a predator will
//	produce.  Actual count will be a randome number
//  between 1 and this number
//---------------------------------------------------
int LifeSimDataParser::getPredatorMaxOffspring()
{
	return m_iPMaxOffspring;
}

//-------------------------------------------------
// Get number of simulation days in a predator's
//  gestation period (time after mating before
//	the offspring are born.
//-------------------------------------------------
double LifeSimDataParser::getPredatorGestationPeriod()
{
	return m_dPGestation;
}

//------------------------------------------
// Get the energy level of offspring at birth
//------------------------------------------
int LifeSimDataParser::getPredatorOffspringEnergyLevel()
{
	return m_iPOffspringEnergy;
}

//---------------------------------------------------------------
// Get all the data on a single predator
// Args:
//		X - pointer to int variable to hold X coordinate
//		Y - pointer to int variable to hold Y coordinate
//		energy - pointer to double variable to hold grazer
//					energy at start of simulation
//		gen - starting address of a char array to hold the
//			predator's genotype.  This will be in the form
//			"AA SS FF" giving the gene pairs for aggression,
//			strength, and speed.  A, S, and F are dominant
//			genes while a, s, and f are recessive.
// Returns: true as long as there was another grazer to read.
//			false when all grazers have been read.
//---------------------------------------------------------------
bool LifeSimDataParser::getPredatorData(int *X, int *Y, int *energy, char *gen)
{
	int dNum = 0;
	char line[128];
	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		// Read to the the current Grazer count
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<PREDATOR>") == 0) // Got one
			{
				if(dNum == m_iPredatorCount)
				{
					// Get data on this one
					while(getNextLine(line, 127))
					{
						// Get the X position
						if(strcmp(line, "<X_POS>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*X = atoi(line); // Set the X position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<Y_POS>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*Y = atoi(line); // Set the Y position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<P_ENERGY_LEVEL>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*energy = atoi(line); // Set the energy level
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<GENOTYPE>") == 0)
						{
							if(getNextLine(line, 127))
							{
								strcpy(gen, line); // Set the genotype
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "</PREDATOR>") == 0)
						{
							m_iPredatorCount++; // Increment for next call to this function
							return true; // Got it
						}
					} // end while
				} // end if(dNum == m_iPredatorCount)
				else
				{
					dNum++; // Check the next one
				}
			}
		}
		inFile->close();
	} // end if file open
	return false; // If we get here we have got all the predators
}

//------------------------------------------
// Get the number of obstacles
//------------------------------------------
int LifeSimDataParser::getObstacleCount()
{
	return m_iNumObstacles;
}

				
//-------------------------------------------------------------------
// Get all the data on a single obstacle
// Args:
//		X - pointer to int variable to hold X coordinate mid-point
//		Y - pointer to int variable to hold Y coordinate mid-point
//		dia - pointer to int variable to hold obstacle radius
//		height - pointer to int variable to hold obstacle height
//		All measures are in Distance Units (DU)
// Returns: true as long as there was another grazer to read.
//			false when all grazers have been read.
//-------------------------------------------------------------------
bool LifeSimDataParser::getObstacleData(int *X, int *Y, int *dia, int *height)
{
	int dNum = 0;
	char line[128];
	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		// Read to the the current Grazer count
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<OBSTACLE>") == 0) // Got one
			{
				if(dNum == m_iObstacleCount)
				{
					// Get data on this one
					while(getNextLine(line, 127))
					{
						// Get the X position
						if(strcmp(line, "<X_POS>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*X = atoi(line); // Set the X position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<Y_POS>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*Y = atoi(line); // Set the Y position
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<O_DIAMETER>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*dia = atoi(line); // Set the radius of this obstacle
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "<O_HEIGHT>") == 0)
						{
							if(getNextLine(line, 127))
							{
								*height = atoi(line); // Set the radius of this obstacle
							}
							else
								return false; // Oops!
						}
						else if(strcmp(line, "</OBSTACLE>") == 0)
						{
							m_iObstacleCount++; // Increment for next call to this function
							return true; // Got it
						}
					} // end while
				} // end if(dNum == m_iObstacleCount)
				else
				{
					dNum++; // Check the next one
				}
			}
		}
		inFile->close();
	} // end if file open
	return false; // If we get here we have got all the obstacles
}

//------------------------------------------------
// Function: getNextLine()
// Purpose: Reads lines from a file and places
//   them in buffer, removing any leading white
//   space.  Skips blank lines. Ignors comment
//   lines starting with <!-- and ending with -->
//   
// Args:  buffer -- char array to read line into.
//        n -- length of buffer.
// Returns: True if a line was successfully read,
//    false if the end of file was encountered.
// Notes: Function provided by instructor.
//------------------------------------------------
bool LifeSimDataParser::getNextLine(char *buffer, int n)
{
    bool    done = false;
	char    tempBuf[128];
	char	*temp;
    while(!done)
    {
        inFile->getline(tempBuf, n); // Read a line from the file

        if(inFile->good())          // If a line was successfully read check it
        {
           if(strlen(tempBuf) == 0)     // Skip any blank lines
               continue;
		   else if(strncmp(tempBuf, "<!--", 4) == 0) // Skip comment lines
			   continue;
           else done = true;    // Got a valid data line so return with this line
        }
        else
        {
            strcpy(buffer, "");  // Clear the buffer array
            return false;        // Flag end of file
        }
    } // end while
	// Remove white space from end of string
	temp = &tempBuf[strlen(tempBuf)]; // point to closing \0
	temp--; // back up 1 space
	while(isspace(*temp))
	{
		*temp = '\0'; // Make it another NULL terminator
		temp--;  // Back up 1 char
	}
	// Remove white space from front of string
	temp = tempBuf;
	while(isspace(*temp)) temp++; // Skip leading white space
	// Copy remainder of string into the buffer
	strcpy(buffer, temp);
    return true;  // Flag a successful read
}
