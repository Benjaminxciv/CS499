#include "mammal.h"

mammal::mammal(int init_energy)
{
    this->energy = init_energy;
}

mammal::~mammal()
{
    
}

void mammal::set_direction(int dir)
{
    this->direction = dir;
}

void mammal::move(int speed)
{
    point* curr_loc = this->get_loc();
    switch(this->direction)
    {
        case up:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case up_right:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case right:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case down_right:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case down:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case down_left:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case left:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
        case up_left:
            this->set_location(curr_loc->x_loc+1, curr_loc->y_loc);
            break;
    }
    this->energy -= this->e_output * (speed / 5);
}

void mammal::sense_shape(int sides, int side_size)
{
    
}


void sense_line1(int line, int count, std::vector<std::vector<bool>>& cells)
{
	//Firstly we have to evaluate the offset:
    int offset = (cells.size() - count) / 2;
    //Then we have to fill the line
    for (int x = offset; x < offset + count; x++)
	{
        cells[x][line] = true;
	}
}

void sense_circle1(std::vector<std::vector<bool>>& cells)
{
	int count = 1;
    for (int line = 0; line < cells[0].size() / 2; line++)
    {
        sense_line1(line, count, cells);
        count += 2;
    }
    sense_line1(cells[0].size() / 2, count, cells);
    count = 1;
    for (int line = cells[0].size() - 1; line > cells[0].size() / 2; line--)
    {
        sense_line1(line, count, cells);
        count += 2;
    }
}

void sense_cone1(std::vector<std::vector<bool>>& cells)
{
    int count = 1;
    for (int line = 0; line < cells[0].size() / 2; line++)
    {
        sense_line1(line, count, cells);
        count += 2;
    }
    sense_line1(cells[0].size() / 2, count, cells);
}

void dos1()
{
    std::vector<std::vector<bool>> cells(3, std::vector<bool>(3, false));
	sense_cone1(cells);
	for (int row = 0; row < cells.size(); row++)
    {
        for (int col = 0; col < cells[0].size(); col++)
        {
            cells[row][col] ? std::cout << (char)219 : std::cout << " ";
        }
        std::cout << std::endl;
    }
	int center = ((cells[0].size() * cells.size()) - 1) / 2;
	std::cout << center << std::endl;
}

void mammal::reproduce()
{

}