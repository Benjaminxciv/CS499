#ifndef DMCO_H
#define DMCO_H

#include <string>
#include "environment_object.h"

class dmco : public environment_object
{
    private:
    public:
        dmco(int, int);
        ~dmco();
        std::string get_type();
};

#endif