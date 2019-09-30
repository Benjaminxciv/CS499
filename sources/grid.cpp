#include "grid.h"

grid_cell::grid_cell()
{
    this->environ_obj = nullptr;
}

grid_cell::~grid_cell()
{

}

grid::grid(int x_size, int y_size)
{
    this->cells = new grid_cell[x_size*y_size];
    this->width = x_size;
    this->height = y_size;
}

grid::~grid()
{
    delete [] this->cells;
}

/*Name: get_instance
Purpose: Get reference to singleton grid object
Parameters: 
    x_size: int
        Defines width of grid
    y_size: int
        Defines height of grid
Returns: Reference to singleton grid object*/
grid& grid::get_instance(int x_size, int y_size)
{
    static grid grid_instance(x_size, y_size);
    return grid_instance;
}


/*Name: get_cell_contents
Purpose: Get pointer to the resident of some cell at X and Y location
Parameters: 
    x_loc: int
        X location of cell to access
    y_loc: int
        Y location of cell to access
Returns: Pointer to resident of cell*/
environment_object* grid::get_cell_contents(int x_loc, int y_loc)
{
    grid_cell* cell = &(this->cells[x_loc*this->height+y_loc]);
    return cell->environ_obj;
}

/*Name: set_cell_contents
Purpose: Set the resident of some cell at X and Y location
Parameters: 
    x_loc: int
        X location of cell to access
    y_loc: int
        Y location of cell to access
    environ_obj: environment_object*
        Resident to place in the cell
Returns: NA*/
void grid::set_cell_contents(int x_loc, int y_loc, environment_object* environ_obj)
{
    grid_cell* cell = &(this->cells[x_loc*this->height+y_loc]);
    cell->environ_obj = environ_obj;
}