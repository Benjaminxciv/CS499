#ifndef GRAZER_H
#define GRAZER_H

#include <string>
#include "environment_object.h"

class grazer : public environment_object
{
    private:
    public:
        grazer(int, int);
        ~grazer();
        std::string get_type();
};

#endif