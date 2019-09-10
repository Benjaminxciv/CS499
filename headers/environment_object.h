#ifndef ENVIRONMENT_OBJECT_H
#define ENVIRONMENT_OBJECT_H

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


};

#endif