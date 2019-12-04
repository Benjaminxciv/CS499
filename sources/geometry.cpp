/*Name: geometry.cpp
Purpose: Defines the tests and final used test for point-line. Allows for the cone of sights to be completed. 
Last edit: 12-2-19
Last editor: AW*/


#include "geometry.h"

using namespace sim_ns;

//Correct function provided from Dr. Mikel Petty at the University of Alabama at Huntsville.
//Contains math for the point-line test. 
bool sim_ns::right_of_line(const point& a, const point& b, const point& c)
{
    return(((b.x_loc - a.x_loc) * (c.y_loc - a.y_loc) - (b.y_loc - a.y_loc) * (c.x_loc - a.x_loc)) <= 0);
}

//Correct function provided from Dr. Mikel Petty at the University of Alabama at Huntsville.
//Contains math for the point-line test. 
bool sim_ns::left_of_line(const point& a, const point& b, const point& c)
{
	return(((b.x_loc - a.x_loc) * (c.y_loc - a.y_loc) - (b.y_loc - a.y_loc) * (c.x_loc - a.x_loc)) >= 0);
}

bool sim_ns::is_in_triangle_right(const point& p1, const point& p2, const point& p3, const point& to_check)
{
    return (right_of_line(p1, p2, to_check) && right_of_line(p2, p3, to_check) && right_of_line(p3, p1, to_check));
}

bool sim_ns::is_in_triangle_left(const point& p1, const point& p2, const point& p3, const point& to_check)
{
	return (left_of_line(p1, p2, to_check) && left_of_line(p2, p3, to_check) && left_of_line(p3, p1, to_check));
}


//Correct function provided from Dr. Mikel Petty at the University of Alabama at Huntsville. 
bool sim_ns::point_in_triangle_petty(const point& p1, const point& p2, const point& p3, const point& to_check)
{
	return is_in_triangle_right(p1, p2, p3, to_check) || is_in_triangle_left(p1, p2, p3, to_check);
}