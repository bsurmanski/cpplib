#ifndef _CPPLIB_GEOM_LINE_HPP
#define _CPPLIB_GEOM_LINE_HPP

#include "vec.hpp"

class Line {
    Vec4 _origin;
    Vec4 _vector;

    public:
    Line(const Vec4 &origin, const Vec4 &vector);

    Vec4 closestPointTo(const Line &o) const;
    Vec4 closestPointTo(const Vec4 &o) const;

    float distanceSqTo(const Line &o) const;
    float distanceSqTo(const Vec4 &o) const;

    float distanceTo(const Line &o) const;
    float distanceTo(const Vec4 &o) const;
};

// Actually a line segment (between _start and _end)
class Segment {
    Vec4 _start;
    Vec4 _end;

    public:
    Segment(const Vec4 &start, const Vec4 &end);

    Vec4 closestPointTo(const Segment &o) const;
    Vec4 closestPointTo(const Vec4 &o) const;

    float distsq(const Vec4 &o);
    float distance(const Vec4 &o);

    float distsq(const Segment &o);
    float distance(const Segment &o);
};

#endif
