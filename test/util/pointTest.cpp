//
// Created by Carolin on 08.04.2020.
//

#include <gtest/gtest.h>
#include <util/Point.hpp>
#include <sstream>

TEST(Point, Point) {
    spy::util::Point p1 = {};
    EXPECT_EQ(p1.x, 0);
    EXPECT_EQ(p1.y, 0);
    EXPECT_TRUE(p1 == p1);
    EXPECT_FALSE(p1 != p1);

    spy::util::Point p2 = {3, 5};
    EXPECT_EQ(p2.x, 3);
    EXPECT_EQ(p2.y, 5);
    EXPECT_TRUE(p2 == p2);
    EXPECT_FALSE(p2 != p2);
    EXPECT_FALSE(p1 == p2);
    EXPECT_FALSE(p2 == p1);
    EXPECT_TRUE(p1 != p2);
    EXPECT_TRUE(p2 != p1);

    spy::util::Point p3 = {5, 3};
    spy::util::Point p4 = p2 + p3;
    EXPECT_EQ(p4.x, 8);
    EXPECT_EQ(p4.y, 8);

    spy::util::Point p5 = p4 - p3;
    EXPECT_EQ(p5.x, p2.x);
    EXPECT_EQ(p5.y, p2.y);

    p2 += {2, 3};
    EXPECT_EQ(p2.x, 5);
    EXPECT_EQ(p2.y, 8);
    EXPECT_FALSE(p1 == p2);
    EXPECT_FALSE(p2 == p1);
    EXPECT_TRUE(p1 != p2);
    EXPECT_TRUE(p2 != p1);

    p1 = {5, 8};
    EXPECT_EQ(p1.x, 5);
    EXPECT_EQ(p1.y, 8);
    EXPECT_TRUE(p1 == p2);
    EXPECT_TRUE(p2 == p1);
    EXPECT_FALSE(p1 != p2);
    EXPECT_FALSE(p2 != p1);

    p2 -= {5, 8};
    EXPECT_EQ(p2.x, 0);
    EXPECT_EQ(p2.y, 0);
    p2 += {-1, 0};
    EXPECT_EQ(p2.x, -1);
    EXPECT_EQ(p2.y, 0);

    std::stringstream stream;
    stream << p1;
    EXPECT_EQ(stream.str(), "[5|8]");
}

TEST(Point, json_decode) {
    auto input = R"({"x":8,"y":13})"_json;
    auto decodedPoint = input.get<spy::util::Point>();

    spy::util::Point point = {8, 13};

    EXPECT_TRUE(decodedPoint == point);
}

TEST(Point, json_encode) {
    spy::util::Point point{8, 13};

    nlohmann::json pointJson = point;

    std::string serialized = pointJson.dump();
    std::string expected = R"({"x":8,"y":13})";
    EXPECT_EQ(expected, serialized);
}
