#ifndef BOULDER_H
#define BOULDER_H

#include "environment_object.h"

class boulder : public environment_object
{
    private:
    public:
        boulder(int, int);
        ~boulder();
        std::string get_type();
};

#endif