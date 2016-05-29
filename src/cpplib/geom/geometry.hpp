#ifndef _CPPLIB_GEOM_GEOMETRY_HPP
#define _CPPLIB_GEOM_GEOMETRY_HPP

#include "vec.hpp"

class Geometry {
    public:
    virtual ~Geometry(){}
    virtual bool contains(Vec4 &o) = 0;
    virtual Vec4 closestPointTo(Vec4 &o) = 0;
};

#endif
