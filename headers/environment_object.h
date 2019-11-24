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
    bool operator==(const point& p1)
    {
        return (x_loc == p1.x_loc && y_loc == p1.y_loc);
    }
};

class environment_object
{
    protected:
        point location;
        int id;
        static int next_id;
    public:
        environment_object();
        environment_object(point);
        ~environment_object();
        
        point get_loc();
        void set_location(point);
        int get_id();
        virtual void act();
        virtual std::string get_type();
        virtual int print_self();
};

#endif