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
    float x_loc;
    float y_loc;
    point() { }
    point(int x, int y) : x_loc(x), y_loc(y) {}
    int distance(const point& p1, point p2) const
    {
        return sqrt(pow((p2.x_loc - p1.x_loc), 2) + pow((p2.y_loc - p1.y_loc), 2));
    }
    bool operator==(const point& p1)
    {
        return (x_loc == p1.x_loc && y_loc == p1.y_loc);
    }
    bool operator==(const point& p1) const
    {
        return (x_loc == p1.x_loc && y_loc == p1.y_loc);
    }
    bool operator<(const point& p1) const
    {
        point origin(0, 0);
        point curr(x_loc, y_loc);
        const point& p_curr = curr;
        return distance(curr, origin) < distance(p1, origin);
    }
};

class environment_object
{
    protected:
        point location;
        int id;
        static int next_id;
        bool garbage;
    public:
        environment_object();
        environment_object(point);
        ~environment_object();
        
        bool is_garbage();
        void become_garbage();
        point get_loc();
        void set_location(point);
        int get_id();
        virtual void act();
        virtual std::string get_type();
        virtual int print_self();
};

#endif