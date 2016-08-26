#include <gtest/gtest.h>

#include "cpplib/geom/line.hpp"

TEST(Line, closestPointToVec4) {
    Line l(Vec4(1, 2, 3), Vec4(0, 1, 1));
    EXPECT_EQ(Vec4(1, 2, 3), l.closestPointTo(Vec4(1, 2, 3)));
    EXPECT_EQ(Vec4(1, 2, 3), l.closestPointTo(Vec4(3, 2, 3)));
    EXPECT_EQ(Vec4(1, 5, 6), l.closestPointTo(Vec4(3, 5, 6)));
    EXPECT_EQ(Vec4(1, -1, 0), l.closestPointTo(Vec4(-6, -1, 0)));
}

TEST(Line, closestPointToLine) {
    Line l1(Vec4(0, 0, 1), Vec4(1, 0, 0));
    Line l2(Vec4(1, 3, 3), Vec4(0, 1, 1));
    EXPECT_EQ(Vec4(1, 0, 1), l1.closestPointTo(l2));
}

TEST(Segment, VecDistance) {
    Segment s(Vec4(1, 0, 0), Vec4(1, 2, 0));
    EXPECT_EQ(1.0f, s.distance(Vec4(0, 0, 0)));
    EXPECT_EQ(1.0f, s.distance(Vec4(1, 3, 0)));
}

TEST(Segment, closestPointToSegment) {
    Segment s(Vec4(1, 0, 0), Vec4(2, 0, 0));
    Segment q(Vec4(1, 1, 0), Vec4(1, 2, 0));
    EXPECT_EQ(Vec4(1, 0, 0), s.closestPointTo(q));
    EXPECT_EQ(Vec4(1, 1, 0), q.closestPointTo(s));

    Segment r(Vec4(1.5f, 1, 0), Vec4(1.5f, -1, 0));
    EXPECT_EQ(Vec4(1.5f, 0, 0), r.closestPointTo(s));
    EXPECT_EQ(Vec4(1.5f, 0, 0), s.closestPointTo(r));
}
