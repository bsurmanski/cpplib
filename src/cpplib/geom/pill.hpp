#ifndef _GEOM_PILL_HPP
#define _GEOM_PILL_HPP

#include "line.hpp"
#include "cpplib/geom/geometry.hpp"

class Ball;

// A pill can be seen as a cylinder capped with spheres
class Pill : public Geometry {
    float _radius;
    float _span; // distance from cylinder center to its top. Doesn't include spherical cap
    Vec4 _center;
    Vec4 _up; // up orientation vector

    public:
    Pill(const Vec4 &center, float radius, float span, Vec4 up=Vec4(0, 1, 0));
    Pill(float x, float y, float z, float radius, float span, Vec4 up=Vec4(0, 1, 0));
    Segment lineSegment() const;
    Pill scaled(float s) const;
    Pill offset(const Vec4 &dv) const;
    Pill offset(float x, float y, float z) const;
    bool collides(const Ball &o) const;
    bool collides(const Pill &o) const;
    virtual bool contains(Vec4 &o) const;
    virtual Vec4 closestPointTo(Vec4 &o) const;
    virtual Vec4 surfaceTangent(Vec4 &n) const;
};

#endif
