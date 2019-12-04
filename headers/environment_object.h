/*
Name: environment_object.h
Purpose: Header file for environment_objects and point. Point represents the x,y location on the simulation grid. 
Last edit: 12-3-19
Last editor: MG
*/


#ifndef ENVIRONMENT_OBJECT_H
#define ENVIRONMENT_OBJECT_H

#include <string>
#include <iostream>

struct point
{
    double x_loc;
    double y_loc;
    double origin_x_loc;
    double origin_y_loc;
    point() { }
    point(double x, double y) : x_loc(x), y_loc(y) {origin_x_loc = -1; origin_y_loc = -1;}
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
        point origin;
        if(origin_x_loc != -1)
        {
            origin = point(origin_x_loc, origin_y_loc);
        }
        else
        {
            origin = point(0,0);
        }
        point curr(x_loc, y_loc);
        const point& p_curr = curr;
        return distance(curr, origin) < distance(p1, origin);
    }
    double operator*(const point& p1) const
    {
        return ((x_loc * p1.x_loc) + (y_loc * p1.y_loc));
    }
    point operator-(const point& p1) const
    {
        return point((x_loc - p1.x_loc), (y_loc - p1.y_loc));
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