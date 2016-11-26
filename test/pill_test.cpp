#include <gtest/gtest.h>

#include "cpplib/geom/ball.hpp"
#include "cpplib/geom/pill.hpp"

TEST(Pill, CollideBall) {
    // test collide with cap
    Ball b1(Vec4(0, 3, 0), 1.1);
    Ball b2(Vec4(0, 3, 0), 0.9);
    Pill p1(Vec4(0, 0, 0), 1, 1);
    EXPECT_TRUE(p1.collides(b1));
    EXPECT_FALSE(p1.collides(b2));

    // test collide with stem
    Pill p2(Vec4(0, 0, 0), 1, 10);
    Ball b3(Vec4(2, 0, 0), 1.1);
    Ball b4(Vec4(2, 0, 0), 0.9);
    EXPECT_TRUE(p2.collides(b3));
    EXPECT_FALSE(p2.collides(b4));

    // test with sideways with cap
    Pill p3(Vec4(0, 5, 0), 1, 10, Vec4(1, 0, 0));
    Ball b5(Vec4(11, 5, 0), 1.1);
    Ball b6(Vec4(11, 0, 0), 0.9);
    EXPECT_TRUE(p3.collides(b5));
    EXPECT_FALSE(p3.collides(b6));

    // test collide sideways with stem
    Ball b7(Vec4(1, 7, 0), 1.1);
    Ball b8(Vec4(1, 7, 0), 0.9);
    EXPECT_TRUE(p3.collides(b7));
    EXPECT_FALSE(p3.collides(b8));
}

TEST(Pill, CollidePill) {
    Pill p1(Vec4(0, 0, 0), 1, 1);
    Pill p2(Vec4(0, 4, 0), 1, 1.1);
    Pill p3(Vec4(0, 4, 0), 1, 0.9);
    EXPECT_TRUE(p1.collides(p2));
    EXPECT_FALSE(p1.collides(p3));

    Pill p4(Vec4(1, 0, 0), 1.1, 1);
    EXPECT_TRUE(p1.collides(p4));
}
