#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <iostream>
#include "environment_object.h"

class plant : public environment_object
{
    private:
    public:
        plant(int, int);
        ~plant();
        std::string get_type();
};

#endif