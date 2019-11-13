/*
Name: predator.h
Purpose: Header file for predators.
Last edit: 09-29-2019
Last editor: MG
*/

#ifndef PREDATOR_H
#define PREDATOR_H

#include "environment_object.h"
#include "mammal.h"

/*
dVal = lsdp->getPredatorMaxSpeedHOD();			// Get max speed for Homozygous Dominant FF
	dVal = lsdp->getPredatorMaxSpeedHED();			// Get max speed for Heterozygous Dominant Ff
	dVal = lsdp->getPredatorMaxSpeedHOR();			// Get max speed for Homozygous Recessive ff
	iVal = lsdp->getPredatorEnergyOutputRate();			// Energy output when moving each 5 DU
	iVal = lsdp->getPredatorEnergyToReproduce();			// Energy level needed to reproduce
	dVal = lsdp->getPredatorMaintainSpeedTime();		// Minutes of simulation to maintain max speed
	iVal = lsdp->getPredatorMaxOffspring();				// Maximum number of offspring when reproducing
	dVal = lsdp->getPredatorGestationPeriod();		// Gestation period in simulation days 
	iVal = lsdp->getPredatorOffspringEnergyLevel();		// Energy level of offspring at birth
*/
class predator : public mammal
{
    private:
        double max_speed_hod;
        double max_speed_hed;
        double max_speed_hor;
        int max_offspring;
        int gestation_period;
        int offspring_energy_level;
    public:
        predator(point, int, int, int, double, double, double, double, double, int, int, int);
        ~predator();
        std::string get_type();
        int print_self();
};

#endif