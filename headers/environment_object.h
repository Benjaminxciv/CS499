/*
Name: environment_object.h
Purpose: Header file for environment_object. 
Last edit: 11-12-2019
Last editor: MG
*/


#ifndef ENVIRONMENT_OBJECT_H
#define ENVIRONMENT_OBJECT_H

#include <string>
#include <iostream>

struct point
{
    int x_loc;
    int y_loc;
    point() {}
    point(int x, int y) : x_loc(x), y_loc(y) {}
};

class environment_object
{
    protected:
        point location;
    public:
        environment_object();
        environment_object(point);
        ~environment_object();
        
        point get_loc();
        void set_location(point); 
        virtual void act();
        virtual std::string get_type();
        virtual int print_self();
};

#endif