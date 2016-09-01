#include "ball.hpp"

#include <string.h>

Ball::Ball(const Vec4 &center, float radius) : _center(center), _radius(radius) {
}

Ball::Ball(float x, float y, float z, float radius) : _center(x, y, z), _radius(radius) {
}

void Ball::scale(float s) {
    _radius *= s;
}

void Ball::move(const Vec4 &o) {
    _center += o;
}

void Ball::move(float x, float y, float z) {
    move(Vec4(x, y, z));
}

bool Ball::collides(const Ball &o) const {
    float drsq = (_radius + o._radius) * (_radius + o._radius);
    float dvsq = _center.distsq(o._center);
    return drsq > dvsq;
}

Vec4 Ball::closestPointTo(Vec4 &o) const {
    if(contains(o)) {
        return o;
    }

    return ((o - _center).normalized() * _radius) + _center;
}

Vec4 Ball::surfaceTangent(Vec4 &n) const {
    return (n.normalized() * _radius) + _center;
}

bool Ball::contains(Vec4 &o) const {
    return _center.distsq(o) < _radius * _radius;
}
