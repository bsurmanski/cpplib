#include <math.h>

#include "line.hpp"

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MIN3(X,Y,Z) MIN(MIN((X),(Y)),(Z))

Line::Line(const Vec4 &origin, const Vec4 &vector) : _origin(origin), _vector(vector) {}

Vec4 Line::closestPointTo(const Line &o) const {
    Vec4 n = o._vector.cross(_vector.cross(o._vector));
    return _origin + _vector.scaled((o._origin - _origin).dot(n) / (_vector.dot(n)));
}

Vec4 Line::closestPointTo(const Vec4 &o) const {
    return o - (o - _origin).orth(_vector);
}

float Line::distanceSqTo(const Line &o) const {
    // This can likely be done much more efficiently
    return (closestPointTo(o) - o.closestPointTo(*this)).lensq();
}

float Line::distanceSqTo(const Vec4 &o) const {
    return ((o - _origin).orth(_vector)).lensq();
}

float Line::distanceTo(const Line &o) const {
    return sqrt(distanceSqTo(o));
}

float Line::distanceTo(const Vec4 &o) const {
    return sqrt(distanceSqTo(o));
}

Segment::Segment(const Vec4 &start, const Vec4 &end) : _start(start), _end(end) {}

Vec4 Segment::closestPointTo(const Segment &o) const {
    Vec4 d1 = _end - _start;
    Vec4 d2 = o._end - o._start;
    Line l1(_start, d1);
    Line l2(o._start, d2);

    Vec4 skew_point = l1.closestPointTo(l2);

    if((skew_point - _start).dot(d1) < 0) return _start;
    if((skew_point - _end).dot(d1) > 0) return _end;
    return skew_point;
}

Vec4 Segment::closestPointTo(const Vec4 &o) const {
    Vec4 d = _end - _start;
    Line l(_start, d);

    Vec4 skew_point = l.closestPointTo(o);

    if((skew_point - _start).dot(d) < 0) return _start;
    if((skew_point - _end).dot(d) > 0) return _end;
    return skew_point;
}

float Segment::distsq(const Vec4 &o) {
    // will either be the distance perpendicular from the point to line (skew),
    // or the distance from one of the segment endings to the point.
    // If the point is between the ends of the line, pick the skew line.
    Vec4 axis = (_end - _start); // vector defined by this line
    if(axis.dot(o - _start) > 0 && axis.dot(o - _end) < 0) {
        return (o - _start).orth(axis).lensq();
    }

    return MIN(o.distsq(_start),
               o.distsq(_end));
}

float Segment::distance(const Vec4 &o) {
    return sqrt(distsq(o));
}

float Segment::distsq(const Segment &o) {
    return (closestPointTo(o) - o.closestPointTo(*this)).lensq();
}

float Segment::distance(const Segment &o) {
    return sqrt(distsq(o));
}
