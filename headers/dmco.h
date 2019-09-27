#ifndef DMCO_H
#define DMCO_H

#include <string>
#include "environment_object.h"
#include "mammal.h"

class dmco : public environment_object, public mammal
{
    private:
    public:
        dmco(int, int, int);
        ~dmco();
        std::string get_type();
};

#endif