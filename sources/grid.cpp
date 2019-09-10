#include <grid.h>

grid_cell::grid_cell()
{
    this->boulder_content = nullptr;
    this->dmco_content = nullptr;
    this->plant_content = nullptr;
    this->predator_content = nullptr;
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
//Purpose: Get resident (obstacle, plant, predator, or DMCO) of some cell at X and Y location
//Parameters: 
    //x_loc: int
        //X location of cell to access
    //y_loc: int
        //Y location of cell to access
    //boulder_content: boulder*
        //nullptr that will be replaced with a valid pointer to a boulder if one exists in the cell
    //plant_content: plant*
        //nullptr that will be replaced with a valid pointer to a plant if one exists in the cell
    //predator_content: predator*
        //nullptr that will be replaced with a valid pointer to a predator if one exists in the cell
    //dmco_content: dmco*
        //nullptr that will be replaced with a valid pointer to a dmco if one exists in the cell
//Last edit: 09/07/19
void grid::get_cell_contents(int x_loc, int y_loc, boulder** boulder_content, plant** plant_content, predator** predator_content, dmco** dmco_content)
{
    grid_cell* cell = &(this->cells[x_loc*this->height+y_loc]);
    if(cell->boulder_content != nullptr)
    {
        *boulder_content = cell->boulder_content;
    }
    else if(cell->plant_content != nullptr)
    {
        *plant_content = cell->plant_content;
    }
    else if(cell->predator_content != nullptr)
    {
        *predator_content = cell->predator_content;
    }
    else if(cell->dmco_content != nullptr)
    {
        *dmco_content = cell->dmco_content;
    }
}

//Name: grid::set_cell_contents
//Purpose: Set resident (obstacle, plant, predator, or DMCO) of some cell at X and Y location
//Parameters: 
    //x_loc: int
        //X location of cell to access
    //y_loc: int
        //Y location of cell to access
    //boulder_content: boulder*
        //Pointer to boulder that will be put in the cell
    //plant_content: plant*
        //Pointer to plant that will be put in the cell
    //predator_content: predator*
        //Pointer to predator that will be put in the cell
    //dmco_content: dmco*
        //Pointer to dmco that will be put in the cell
//Last edit: 09/07/19
void grid::set_cell_contents(int x_loc, int y_loc, boulder* boulder_content, plant* plant_content, predator* predator_content, dmco* dmco_content)
{
    grid_cell* cell = &(this->cells[x_loc*this->height+y_loc]);
    if(boulder_content != nullptr)
    {
        cell->boulder_content = boulder_content;
    }
    else if(plant_content != nullptr)
    {
        cell->plant_content = plant_content;
    }
    else if(predator_content != nullptr)
    {
        cell->predator_content = predator_content;
    }
    else if(dmco_content != nullptr)
    {
        cell->dmco_content = dmco_content;
    }
}