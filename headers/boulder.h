/*
Name: boulder.h
Purpose: Header file for all of the boulder information
Last edit: 09-29-19
Last editor: MG
*/


#ifndef BOULDER_H
#define BOULDER_H

#include "environment_object.h"
#include <iostream>

class boulder : public environment_object
{
    private:
    public:
        boulder(int, int);
        ~boulder();
        std::string get_type();
        int print_self();
};

#endif