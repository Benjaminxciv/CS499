/*******************************************************************
*   grid.h
*   Date: 09/04/19
*******************************************************************/

#ifndef GRID_H
#define GRID_H
#include "environment_object.h"

struct grid_cell
{
	environment_object* environ_obj;
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
		environment_object* get_cell_contents(int, int);
		void set_cell_contents(int, int, environment_object*);
		static grid& get_instance(int, int);
};

#endif