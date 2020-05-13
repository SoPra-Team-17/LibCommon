/**
 * @file   lineOfSightTests.cpp
 * @author Dominik Authaler
 * @date   19.04.2020 (creation)
 * @brief  Unit tests for the line of sight implementation.
 */

#include <gtest/gtest.h>
#include <datatypes/scenario/Scenario.hpp>
#include <datatypes/scenario/FieldMap.hpp>

class LineOfSight : public ::testing::Test {
    protected:
        nlohmann::json input = R"({ "scenario": [
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"],
            ["WALL", "FIREPLACE", "WALL", "BAR_TABLE",      "BAR_SEAT", "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_TABLE", "WALL", "ROULETTE_TABLE", "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE",     "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE", "WALL"],
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
            ]})"_json;

        spy::scenario::Scenario decodedScenario = input.get<spy::scenario::Scenario>();

        spy::scenario::FieldMap field{decodedScenario};
};

TEST_F(LineOfSight, InvalidArguments) {
    EXPECT_ANY_THROW(bool _ = field.isLineOfSightFree({-1, 0}, {0, 0}));
    EXPECT_ANY_THROW(bool _ = field.isLineOfSightFree({0, 0}, {0, 7}));
    EXPECT_TRUE(field.isLineOfSightFree({0, 0}, {0, 0}));
}

TEST_F(LineOfSight, HorizontalLine) {
    EXPECT_FALSE(field.isLineOfSightFree({0, 0}, {2, 0}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 3}, {1, 5}));
    EXPECT_FALSE(field.isLineOfSightFree({2, 0}, {0, 0}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 5}, {1, 3}));
}

TEST_F(LineOfSight, VerticalLine) {
    EXPECT_FALSE(field.isLineOfSightFree({0, 0}, {0, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({4, 1}, {4, 5}));

    EXPECT_FALSE(field.isLineOfSightFree({0, 2}, {0, 0}));
    EXPECT_TRUE(field.isLineOfSightFree({4, 5}, {4, 1}));
}

TEST_F(LineOfSight, DiagonalLine) {
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {0, 0}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {1, 0}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {2, 0}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {3, 0}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {4, 0}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {5, 0}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {6, 0}));

    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {0, 0}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {1, 1}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {2, 1}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {3, 1}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {4, 1}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {5, 1}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {6, 1}));

    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {0, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {2, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {3, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {4, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {5, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {6, 2}));

    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {0, 3}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {1, 3}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {2, 3}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {3, 3}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {4, 3}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {5, 3}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {6, 3}));

    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {0, 4}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {1, 4}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {2, 4}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {3, 4}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {4, 4}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {5, 4}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {6, 4}));

    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {0, 5}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {1, 5}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {2, 5}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {3, 5}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {4, 5}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {5, 5}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {6, 5}));

    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {0, 6}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {1, 6}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 2}, {2, 6}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {3, 6}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {4, 6}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {5, 6}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 2}, {6, 6}));

    EXPECT_TRUE(field.isLineOfSightFree({3, 3}, {2, 4}));
    EXPECT_TRUE(field.isLineOfSightFree({2, 4}, {3, 5}));

    EXPECT_FALSE(field.isLineOfSightFree({0, 0}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({1, 0}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({2, 0}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({3, 0}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({4, 0}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({5, 0}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({6, 0}, {1, 2}));

    EXPECT_FALSE(field.isLineOfSightFree({0, 0}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 1}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({2, 1}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({3, 1}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({4, 1}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({5, 1}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({6, 1}, {1, 2}));

    EXPECT_TRUE(field.isLineOfSightFree({0, 2}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({2, 2}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({3, 2}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({4, 2}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({5, 2}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({6, 2}, {1, 2}));

    EXPECT_TRUE(field.isLineOfSightFree({0, 3}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 3}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({2, 3}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({3, 3}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({4, 3}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({5, 3}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({6, 3}, {1, 2}));

    EXPECT_FALSE(field.isLineOfSightFree({0, 4}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 4}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({2, 4}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({3, 4}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({4, 4}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({5, 4}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({6, 4}, {1, 2}));

    EXPECT_FALSE(field.isLineOfSightFree({0, 5}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 5}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({2, 5}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({3, 5}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({4, 5}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({5, 5}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({6, 5}, {1, 2}));

    EXPECT_FALSE(field.isLineOfSightFree({0, 6}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({1, 6}, {1, 2}));
    EXPECT_TRUE(field.isLineOfSightFree({2, 6}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({3, 6}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({4, 6}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({5, 6}, {1, 2}));
    EXPECT_FALSE(field.isLineOfSightFree({6, 6}, {1, 2}));

    EXPECT_TRUE(field.isLineOfSightFree({2, 4}, {3, 3}));
    EXPECT_TRUE(field.isLineOfSightFree({3, 5}, {2, 4}));
}



