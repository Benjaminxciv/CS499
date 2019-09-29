/*
Name: simulation.h
Purpose: Contains all header file information for simulation.cpp, controls flow of Life Simulation
Last edit: 
Last editor: 
*/


#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include "grid.h"
#include "boulder.h"
#include "LifeSimDataParser.h"
#include "plant.h"
#include "predator.h"
#include "grazer.h"

class simulation
{
    private:
        int tick_speed;
    public:
        simulation();
        ~simulation();
        void run_sim();
        void set_tick_speed(int);
};

#endif