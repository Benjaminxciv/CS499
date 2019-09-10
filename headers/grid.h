/*******************************************************************
*   grid.h
*   Date: 09/04/19
*******************************************************************/

#ifndef GRID_H
#define GRID_H

#include "boulder.h"
#include "plant.h"
#include "predator.h"
#include "dmco.h"

struct grid_cell
{
	boulder* boulder_content;
	plant* plant_content;
	predator* predator_content;
	dmco* dmco_content;
	grid_cell();
	~grid_cell();
};

class grid
{
	private:
		int width;
		int height;
		grid_cell* cells;
		grid(int, int);
		~grid();
	public:
		void get_cell_contents(int, int, boulder** = nullptr, plant** = nullptr, predator** = nullptr, dmco** = nullptr);
		void set_cell_contents(int, int, boulder* = nullptr, plant* = nullptr, predator* = nullptr, dmco* = nullptr);
		static grid& get_instance(int, int);
};

#endif