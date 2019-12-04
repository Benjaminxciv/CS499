/*
Name: grid.h
Purpose: Header file for the grid. 
Last edit: 12-3-19
Last editor: MG
*/

#ifndef GRID_H
#define GRID_H

#include <iostream>
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
	public:
		grid(int, int);
		~grid();
	public:
		environment_object* get_cell_contents(point);
		void set_cell_contents(point, environment_object*);
		void print_grid();
		void print_cols();
		void print_rows();
		int get_height();
		int get_width();
		bool check_bounds(point);
};

#endif