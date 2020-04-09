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

    spy::util::Point p2 = {3, 5};
    EXPECT_EQ(p2.getX(), 3);
    EXPECT_EQ(p2.getY(), 5);
    EXPECT_TRUE(p2 == p2);
    EXPECT_FALSE(p2 != p2);
    EXPECT_FALSE(p1 == p2);
    EXPECT_FALSE(p2 == p1);
    EXPECT_TRUE(p1 != p2);
    EXPECT_TRUE(p2 != p1);

    spy::util::Point p3 = {5, 3};
    spy::util::Point p4 = p2 + p3;
    EXPECT_EQ(p4.getX(), 8);
    EXPECT_EQ(p4.getY(), 8);

    spy::util::Point p5 = p4 - p3;
    EXPECT_EQ(p5.getX(), p2.getX());
    EXPECT_EQ(p5.getY(), p2.getY());

    p2 += {2, 3};
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

    p2 -= {5, 8};
    EXPECT_EQ(p2.getX(), 0);
    EXPECT_EQ(p2.getY(), 0);
    p2 += {-1, 0};
    EXPECT_EQ(p2.getX(), -1);
    EXPECT_EQ(p2.getY(), 0);
}

TEST(JSON_Decode, Point) {
    auto input = R"({"x":8,"y":13})"_json;
    auto decodedPoint = input.get<spy::util::Point>();

    spy::util::Point point = {8, 13};

    EXPECT_TRUE(decodedPoint == point);
}

TEST(JSON_Encode, Point) {
    spy::util::Point point(8, 13);

    nlohmann::json pointJson = point;

    std::string serialized = pointJson.dump();
    std::string expected = R"({"x":8,"y":13})";
    EXPECT_EQ(expected, serialized);
}
