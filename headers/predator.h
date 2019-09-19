#ifndef PREDATOR_H
#define PREDATOR_H

#include "environment_object.h"

class predator : public environment_object
{
    private:
    public:
        predator(int, int);
        ~predator();
        std::string get_type();
};

#endif