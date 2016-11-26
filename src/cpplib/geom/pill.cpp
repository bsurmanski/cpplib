#include "pill.hpp"
#include "ball.hpp"

#define SQ(X) ((X) * (X))

Pill::Pill(const Vec4 &center, float radius, float span, Vec4 up) :
    _center(center), _radius(radius), _span(span), _up(up) {}

Pill::Pill(float x, float y, float z, float radius, float span, Vec4 up) :
    _center(x, y, z), _radius(radius), _span(span), _up(up) {}

Segment Pill::lineSegment() const {
    return Segment(_center - (_up * _span), _center + (_up * _span));
}

Pill Pill::scaled(float s) const {
    return Pill(_center, _radius * s, _span * s, _up);
}

Pill Pill::offset(const Vec4 &dv) const {
    return Pill(_center + dv, _radius, _span, _up);
}

Pill Pill::offset(float x, float y, float z) const {
    return offset(Vec4(x, y, z));
}

// Pill collision is pretty simple. A pill is basically just a fat line.
bool Pill::collides(const Ball &o) const {
    return lineSegment().distsq(o.center()) < SQ(o.radius() + _radius);
}

bool Pill::collides(const Pill &o) const {
    return lineSegment().distsq(o.lineSegment()) < SQ(o._radius + _radius);
}

bool Pill::contains(Vec4 &o) const {
    return lineSegment().distsq(o) < SQ(_radius);
}

Vec4 Pill::closestPointTo(Vec4 &o) const {
    Vec4 closest = lineSegment().closestPointTo(o);

    // Pill contains point
    if(closest.distsq(o) < SQ(_radius)) {
        return o;
    }

    return closest + (o - closest).normalized() * _radius;
}

Vec4 Pill::surfaceTangent(Vec4 &n) const {
    //TODO
}
