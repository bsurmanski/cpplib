#ifndef _GEOM_BALL_HPP
#define _GEOM_BALL_HPP

#include "vec.hpp"
#include "geometry.hpp"

class Ball : public Geometry {
    float _radius;
    Vec4 _center;

    public:
    Ball(const Vec4 &_center, float radius);
    Ball(float x, float y, float z, float radius);
    void set_center(const Vec4 &_center);
    void set_center(float x, float y, float z);
    void set_radius(float r);
    void scale(float s);
    void move(const Vec4 &dv);
    void move(float x, float y, float z);
    bool collides(const Ball &o);
    virtual bool contains(Vec4 &o);
    virtual Vec4 closestPointTo(Vec4 &o);
};

#endif
