#include <iostream>
#include <grid.h>
#include <boulder.h>


int main()
{
    grid& sim_grid = grid::get_instance(10,10);
    boulder* bould = new boulder(1,1);
    sim_grid.set_cell_contents(1, 1, bould);
    boulder* bould2 = nullptr;
    sim_grid.get_cell_contents(1,1,&bould2);
    point* p = bould2->get_loc();
    std::cout << p->x_loc << std::endl << p->y_loc << std::endl;
    std::cin.get();
    return 0;
}