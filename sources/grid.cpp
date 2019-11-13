/*Name: grid.cpp
Purpose: Holds functions for the grid, including getting & setting cells contents
Last edit: 10-01-19
Last editor: AW*/

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


/*Name: get_cell_contents
Purpose: Get pointer to the resident of some cell at X and Y location
Parameters: 
    x_loc: int
        X location of cell to access
    y_loc: int
        Y location of cell to access
Returns: Pointer to resident of cell*/
environment_object* grid::get_cell_contents(point location)
{
    grid_cell* cell = &(this->cells[location.x_loc*this->height+location.y_loc]);
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
void grid::set_cell_contents(point location, environment_object* environ_obj)
{
    grid_cell* cell = &(this->cells[location.x_loc*this->height+location.y_loc]);
    cell->environ_obj = environ_obj;
}

/*Name: grid::print_grid
Purpose: calls print_cols and print_rows functions 
Parameters: 
    width: int
    width of enviroment boundary
    height: int
    height of enviroment boundary
Returns: N/A
Last edit:
    BP 10/1/19
*/
void grid::print_grid()
{
    print_cols();
    print_rows();
    print_cols();  
}

/*Name: grid::print_cols
Purpose: print the column header of the simulation grid from given width boundary
Parameters: 
    width: int
        width of enviroment boundary
Last edit:
    BP 10/1/19
*/
void grid::print_cols()
{
    int du_scale = 25;
    std::string column_space =  "     ";
    std::cout << column_space;
    for(int i = 1; i < (this->width/du_scale)+1; i++)
    {
        std::cout.fill('0');
        std::cout.width(3);
        std::cout << i*du_scale << " ";
    }
    std::cout << std::endl;
}

//Name: grid::print_rows
//Purpose: print the rows of the simulation grid
//Parameters: 
    //width: int
        //width of enviroment boundary
    //height: int
        //height of enviroment boundary
//Last edit: 09/29/19
void grid::print_rows()
{
    int du_scale = 25;
    for (int j = 0; j < (this->height/du_scale)+1; j++)
    {   
        std::cout.fill('0');
        std::cout.width(3);
        std::cout << j*du_scale;

        for(int k = 0; k < (this->width/du_scale); k++)
        {
            std::cout.fill(' ');
            std::cout.width(4);
            std::cout << "*";
        } 
        std::cout << std::endl;
    }      
}