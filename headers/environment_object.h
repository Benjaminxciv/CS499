/*
Name: environment_object.h
Purpose: Header file for environment_object. 
Last edit: 
Last editor: 
*/


#ifndef ENVIRONMENT_OBJECT_H
#define ENVIRONMENT_OBJECT_H

#include <string>

struct point
{
    int x_loc;
    int y_loc;
};

class environment_object
{
    private:
        point* location;
    public:
        environment_object(int, int);
        ~environment_object();
        
        point* get_loc();
        void set_location(int, int); 
        virtual void act();
        virtual std::string get_type();
        virtual std::string print_self();
};

#endif