#ifndef _CPPLIB_GEOM_GEOMETRY_HPP
#define _CPPLIB_GEOM_GEOMETRY_HPP

#include "vec.hpp"
#include <math.h>

class Geometry {
    public:
    virtual ~Geometry(){}
    virtual bool contains(Vec4 &o) = 0;
    virtual Vec4 closestPointTo(Vec4 &o) = 0;

    virtual float dist(Vec4 &o) {
        return sqrt(distsq(o));
    }

    virtual float distsq(Vec4 &o) {
        return (o - closestPointTo(o)).lensq();
    }

    // given an infinite surface with normal '-n', where is the tangent point of
    // this piece of geometry? This Results in the point on this geometry that
    // is the furthest along the 'normal' axis.
    //
    // Eg. If this is a perfect unit sphere centered at the origin, asking for
    // the surface tangent at (0, 1, 0) will return (0, 1, 0), since this is
    // the further point on the sphere along said normal axis.
    virtual Vec4 surfaceTangent(Vec4 &n) = 0;
};

#endif
