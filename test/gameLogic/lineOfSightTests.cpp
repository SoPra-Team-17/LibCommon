/**
 * @file   lineOfSightTests.cpp
 * @author Dominik Authaler
 * @date   19.04.2020 (creation)
 * @brief  Unit tests for the line of sight implementation.
 */

#include <gtest/gtest.h>
#include <scenario/Scenario.hpp>
#include <scenario/FieldMap.hpp>

auto input = R"({ "scenario": [
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"],
            ["WALL", "FIREPLACE", "WALL", "BAR_TABLE",      "BAR_SEAT", "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_TABLE", "WALL", "ROULETTE_TABLE", "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE",     "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE", "WALL"],
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
            ]})"_json;

TEST(LineOfSight, InvalidArguments) {
    spy::scenario::Scenario decodedScenario;
    decodedScenario = input.get<spy::scenario::Scenario>();

    spy::scenario::FieldMap field(decodedScenario);

    EXPECT_ANY_THROW(bool _ = field.isLineOfSightFree(spy::util::Point(-1, 0), spy::util::Point(0, 0)));
    EXPECT_ANY_THROW(bool _ = field.isLineOfSightFree(spy::util::Point(0, 0), spy::util::Point(0, 7)));
    EXPECT_ANY_THROW(bool _ = field.isLineOfSightFree(spy::util::Point(0, 0), spy::util::Point(0, 0)));
}

TEST(LineOfSight, HorizontalLine) {
    spy::scenario::Scenario decodedScenario;
    decodedScenario = input.get<spy::scenario::Scenario>();

    spy::scenario::FieldMap field(decodedScenario);

    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(0, 0), spy::util::Point(2, 0)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 3), spy::util::Point(1, 5)));
}

TEST(LineOfSight, VerticalLine) {
    spy::scenario::Scenario decodedScenario;
    decodedScenario = input.get<spy::scenario::Scenario>();

    spy::scenario::FieldMap field(decodedScenario);

    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(0, 0), spy::util::Point(0, 2)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(4, 1), spy::util::Point(4, 5)));
}

TEST(LineOfSight, DiagonalLine) {
    spy::scenario::Scenario decodedScenario;
    decodedScenario = input.get<spy::scenario::Scenario>();

    spy::scenario::FieldMap field(decodedScenario);

    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(0, 0)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(1, 0)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(2, 0)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(3, 0)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(4, 0)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(5, 0)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(6, 0)));

    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(0, 0)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(1, 1)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(2, 1)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(3, 1)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(4, 1)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(5, 1)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(6, 1)));

    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(0, 2)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(2, 2)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(3, 2)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(4, 2)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(5, 2)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(6, 2)));

    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(0, 3)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(1, 3)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(2, 3)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(3, 3)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(4, 3)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(5, 3)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(6, 3)));

    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(0, 4)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(1, 4)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(2, 4)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(3, 4)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(4, 4)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(5, 4)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(6, 4)));

    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(0, 5)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(1, 5)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(2, 5)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(3, 5)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(4, 5)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(5, 5)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(6, 5)));

    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(0, 6)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(1, 6)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(2, 6)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(3, 6)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(4, 6)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(5, 6)));
    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(1, 2), spy::util::Point(6, 6)));

    EXPECT_FALSE(field.isLineOfSightFree(spy::util::Point(3, 3), spy::util::Point(2, 4)));
    EXPECT_TRUE(field.isLineOfSightFree(spy::util::Point(2, 4), spy::util::Point(3, 5)));
}



