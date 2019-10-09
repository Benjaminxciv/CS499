#ifndef PREDATOR_H
#define PREDATOR_H

#include "environment_object.h"
#include "mammal.h"

class predator : public environment_object, public mammal
{
    private:
    public:
        predator(int, int, int);
        ~predator();
        void smell();
        std::string get_type();
};

#endif