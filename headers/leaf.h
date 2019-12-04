/*
Name: leaf.h
Purpose: Class containing definitions for leaf environment_object.
Last edit: 12-3-2019
Last editor: MG
*/

#ifndef LEAF_H
#define LEAF_H

#include <string.h>
#include "environment_object.h"
#include <stdlib.h>


class leaf : public environment_object
{
private:
public:
    leaf();
    leaf(point);
    ~leaf();
    std::string get_type();
    void act();
};

#endif LEAF_H