//
// Created by Carolin on 08.04.2020.
//

#include <gtest/gtest.h>
#include <util/Point.hpp>

TEST(point, Point) {
    spy::util::Point p1 = {};
    EXPECT_EQ(p1.getX(), 0);
    EXPECT_EQ(p1.getY(), 0);
    EXPECT_TRUE(p1 == p1);
    EXPECT_FALSE(p1 != p1);
    EXPECT_TRUE(p1.isValid());

    spy::util::Point p2 = {3, 5};
    EXPECT_EQ(p2.getX(), 3);
    EXPECT_EQ(p2.getY(), 5);
    EXPECT_TRUE(p2 == p2);
    EXPECT_FALSE(p2 != p2);
    EXPECT_TRUE(p2.isValid());
    EXPECT_FALSE(p1 == p2);
    EXPECT_FALSE(p2 == p1);
    EXPECT_TRUE(p1 != p2);
    EXPECT_TRUE(p2 != p1);

    p2.translate(2, 3);
    EXPECT_EQ(p2.getX(), 5);
    EXPECT_EQ(p2.getY(), 8);
    EXPECT_FALSE(p1 == p2);
    EXPECT_FALSE(p2 == p1);
    EXPECT_TRUE(p1 != p2);
    EXPECT_TRUE(p2 != p1);

    p1.setLocation(5, 8);
    EXPECT_EQ(p1.getX(), 5);
    EXPECT_EQ(p1.getY(), 8);
    EXPECT_TRUE(p1 == p2);
    EXPECT_TRUE(p2 == p1);
    EXPECT_FALSE(p1 != p2);
    EXPECT_FALSE(p2 != p1);

    p2.translate(-5, -8);
    EXPECT_EQ(p2.getX(), 0);
    EXPECT_EQ(p2.getY(), 0);
    EXPECT_TRUE(p2.isValid());
    p2.translate(-1, 0);
    EXPECT_EQ(p2.getX(), -1);
    EXPECT_EQ(p2.getY(), 0);
    EXPECT_FALSE(p2.isValid());
}
