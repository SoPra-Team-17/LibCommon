/**
 * @file   scenarioTest.cpp
 * @author Dominik Authaler
 * @date   07.04.2020 (creation)
 * @brief  Unit tests for the Scenario classes.
 */

#include <gtest/gtest.h>
#include <scenario/Scenario.hpp>

TEST(Scenario, ScenarioDecoding) {
    auto input = R"({ "scenario": [
		["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"],
		["WALL", "FIREPLACE", "WALL", "BAR_TABLE",      "BAR_SEAT", "FREE", "WALL"],
		["WALL", "FREE",      "FREE", "FREE",           "FREE",     "FREE", "WALL"],
		["WALL", "BAR_TABLE", "FREE", "ROULETTE_TABLE", "FREE",     "FREE", "WALL"],
		["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE",     "FREE", "WALL"],
		["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE", "WALL"],
		["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
	    ]})"_json;

    spy::scenario::Scenario decodedScenario;
    EXPECT_NO_THROW(decodedScenario = input.get<spy::scenario::Scenario>());

    EXPECT_EQ(decodedScenario.getField(0, 0), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(1, 0), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(2, 0), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(3, 0), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(4, 0), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(5, 0), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(6, 0), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(decodedScenario.getField(0, 1), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(1, 1), spy::scenario::FieldStateEnum::FIREPLACE);
    EXPECT_EQ(decodedScenario.getField(2, 1), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(3, 1), spy::scenario::FieldStateEnum::BAR_TABLE);
    EXPECT_EQ(decodedScenario.getField(4, 1), spy::scenario::FieldStateEnum::BAR_SEAT);
    EXPECT_EQ(decodedScenario.getField(5, 1), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(6, 1), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(decodedScenario.getField(0, 2), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(1, 2), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(2, 2), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(3, 2), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(4, 2), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(5, 2), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(6, 2), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(decodedScenario.getField(0, 3), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(1, 3), spy::scenario::FieldStateEnum::BAR_TABLE);
    EXPECT_EQ(decodedScenario.getField(2, 3), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(3, 3), spy::scenario::FieldStateEnum::ROULETTE_TABLE);
    EXPECT_EQ(decodedScenario.getField(4, 3), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(5, 3), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(6, 3), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(decodedScenario.getField(0, 4), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(1, 4), spy::scenario::FieldStateEnum::BAR_SEAT);
    EXPECT_EQ(decodedScenario.getField(2, 4), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(3, 4), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(4, 4), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(5, 4), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(6, 4), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(decodedScenario.getField(0, 5), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(1, 5), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(2, 5), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(3, 5), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(4, 5), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(5, 5), spy::scenario::FieldStateEnum::SAFE);
    EXPECT_EQ(decodedScenario.getField(6, 5), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(decodedScenario.getField(0, 6), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(1, 6), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(2, 6), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(3, 6), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(4, 6), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(5, 6), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(6, 6), spy::scenario::FieldStateEnum::WALL);
}
