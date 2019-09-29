#include "grid.h"
#include <iostream>

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

grid& grid::get_instance(int x_size, int y_size)
{
    static grid grid_instance(x_size, y_size);
    return grid_instance;
}

//Name: grid::get_cell_contents
//Purpose: Get resident of some cell at X and Y location
//Parameters: 
    //x_loc: int
        //X location of cell to access
    //y_loc: int
        //Y location of cell to access
//Last edit: 09/18/19
environment_object* grid::get_cell_contents(int x_loc, int y_loc)
{
    grid_cell* cell = &(this->cells[x_loc*this->height+y_loc]);
    return cell->environ_obj;
}

//Name: grid::set_cell_contents
//Purpose: Set resident of some cell at X and Y location
//Parameters: 
    //x_loc: int
        //X location of cell to access
    //y_loc: int
        //Y location of cell to access
    //environ_obj: environment_object*
        //Pointer to environment_object that will be put in the cell
//Last edit: 09/18/19
void grid::set_cell_contents(int x_loc, int y_loc, environment_object* environ_obj)
{
    grid_cell* cell = &(this->cells[x_loc*this->height+y_loc]);
    cell->environ_obj = environ_obj;
}

//Name: grid::print_gridle
//Purpose: calls print_cols and print_rows functions 
//Parameters: 
    //width: int
        //width of enviroment boundary
    //height: int
        //height of enviroment boundary
//Last edit: 09/29/19
void grid::print_grid(int width , int height)
{
    print_cols(width);
    print_rows(width, height);
    print_cols(width);  
}

//Name: grid::print_cols
//Purpose: print the column header of the simulation grid from given width boundary
//Parameters: 
    //width: int
        //width of enviroment boundary
//Last edit: 09/29/19
void grid::print_cols(int width)
{
    std::string column_space =  "     ";
    std::cout << column_space;
    for(int i = 1; i < (width/25)+1; i++)
    {
        std::cout.fill('0');
        std::cout.width(3);
        std::cout << i*25 << " ";
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
void grid::print_rows(int width,int height)
{
    for (int j = 0; j < (height/25)+1; j++)
    {   
        std::cout.fill('0');
        std::cout.width(3);
        std::cout << j*25;

        for(int k = 0; k < (width/25); k++)
        {
            std::cout.fill(' ');
            std::cout.width(4);
            std::cout << "*";
        } 
        std::cout << std::endl;
    }      
}