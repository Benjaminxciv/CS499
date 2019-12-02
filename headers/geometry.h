#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "environment_object.h"

namespace sim_ns
{
    bool right_of_line(const point&, const point&, const point&);
    bool left_of_line(const point&, const point&, const point&);
    bool is_in_triangle_right(const point&, const point&, const point&, const point&);
    bool is_in_triangle_left(const point&, const point&, const point&, const point&);
    bool point_in_triangle_petty(const point&, const point&, const point&, const point&);
}

#endif