#ifndef _GEOM_BALL_HPP
#define _GEOM_BALL_HPP

#include "cpplib/geom/geometry.hpp"

class Ball : public Geometry {
    float _radius;
    Vec4 _center;

    public:
    Ball(const Vec4 &_center, float radius);
    Ball(float x, float y, float z, float radius);
    void scale(float s);
    void move(const Vec4 &dv);
    void move(float x, float y, float z);
    const Vec4 &center() const { return _center; }
    float radius() const { return _radius; }
    bool collides(const Ball &o) const;
    virtual bool contains(Vec4 &o) const;
    virtual Vec4 closestPointTo(Vec4 &o) const;
    virtual Vec4 surfaceTangent(Vec4 &n) const;
};

#endif
