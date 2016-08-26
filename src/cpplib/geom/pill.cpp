#include "pill.hpp"
#include "ball.hpp"

#define SQ(X) ((X) * (X))

Pill::Pill(const Vec4 &center, float radius, float span) :
    _center(center), _radius(radius), _span(span), _up(0, 1, 0) {}

Pill::Pill(float x, float y, float z, float radius, float span) :
    _center(x, y, z), _radius(radius), _span(span), _up(0, 1, 0) {}

Segment Pill::lineSegment() const {
    return Segment(_center - (_up * _span), _center + (_up * _span));
}

void Pill::set_center(const Vec4 &center) {
    _center = center;
}

void Pill::set_center(float x, float y, float z) {
    set_center(Vec4(x, y, z));
}

void Pill::set_radius(float r) {
    _radius = r;
}

void Pill::set_span(float s) {
    _span = s;
}

void Pill::scale(float s) {
    _span *= s;
    _radius *= s;
}

void Pill::move(const Vec4 &dv) {
    _center += dv;
}

void Pill::move(float x, float y, float z) {
    move(Vec4(x, y, z));
}

// Pill collision is pretty simple. A pill is basically just a fat line.
bool Pill::collides(const Ball &o) {
    return lineSegment().distsq(o.center()) < SQ(o.radius() + _radius);
}

bool Pill::collides(const Pill &o) {
    return lineSegment().distsq(o.lineSegment()) < SQ(_radius + o._radius);
}

bool Pill::contains(Vec4 &o) {
    return lineSegment().distsq(o) < SQ(_radius);
}

Vec4 Pill::closestPointTo(Vec4 &o) {
    Vec4 closest = lineSegment().closestPointTo(o);

    // Pill contains point
    if(closest.distsq(o) < SQ(_radius)) {
        return o;
    }

    return closest + (o - closest).normalized() * _radius;
}

Vec4 Pill::surfaceTangent(Vec4 &n) {
    //TODO
}
