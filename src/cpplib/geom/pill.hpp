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
    Pill(const Vec4 &center, float radius, float span);
    Pill(float x, float y, float z, float radius, float span);
    Segment lineSegment() const;
    void set_center(const Vec4 &center);
    void set_center(float x, float y, float z);
    void set_radius(float r);
    void set_span(float s);
    void scale(float s);
    void move(const Vec4 &dv);
    void move(float x, float y, float z);
    bool collides(const Ball &o);
    bool collides(const Pill &o);
    virtual bool contains(Vec4 &o);
    virtual Vec4 closestPointTo(Vec4 &o);
    virtual Vec4 surfaceTangent(Vec4 &n);
};

#endif
