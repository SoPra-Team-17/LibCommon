/**
 * @file   scenarioTest.cpp
 * @author Dominik Authaler
 * @date   07.04.2020 (creation)
 * @brief  Unit tests for the Scenario classes.
 */

#include <gtest/gtest.h>
#include <scenario/Scenario.hpp>
#include <scenario/FieldMap.hpp>

TEST(Scenario, ScenarioDecodingEncoding) {
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

    EXPECT_EQ(decodedScenario.getField(spy::util::Point(0, 4)), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(1, 4)), spy::scenario::FieldStateEnum::BAR_SEAT);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(2, 4)), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(3, 4)), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(4, 4)), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(5, 4)), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(6, 4)), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(decodedScenario.getField(spy::util::Point(0, 5)), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(1, 5)), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(2, 5)), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(3, 5)), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(4, 5)), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(5, 5)), spy::scenario::FieldStateEnum::SAFE);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(6, 5)), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(decodedScenario.getField(spy::util::Point(0, 6)), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(1, 6)), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(2, 6)), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(3, 6)), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(4, 6)), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(5, 6)), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField(spy::util::Point(6, 6)), spy::scenario::FieldStateEnum::WALL);

    nlohmann::json json;
    EXPECT_NO_THROW(json = decodedScenario);
    EXPECT_EQ(json.dump(), input.dump());
}

TEST(Scenario, FieldMapConstruction) {
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

    spy::scenario::FieldMap field(decodedScenario);

    EXPECT_EQ(field.getField(0, 0).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(1, 0).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(2, 0).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(3, 0).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(4, 0).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(5, 0).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(6, 0).getFieldState(), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(field.getField(0, 1).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(1, 1).getFieldState(), spy::scenario::FieldStateEnum::FIREPLACE);
    EXPECT_EQ(field.getField(2, 1).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(3, 1).getFieldState(), spy::scenario::FieldStateEnum::BAR_TABLE);
    EXPECT_EQ(field.getField(4, 1).getFieldState(), spy::scenario::FieldStateEnum::BAR_SEAT);
    EXPECT_EQ(field.getField(5, 1).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(6, 1).getFieldState(), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(field.getField(0, 2).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(1, 2).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(2, 2).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(3, 2).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(4, 2).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(5, 2).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(6, 2).getFieldState(), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(field.getField(0, 3).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(1, 3).getFieldState(), spy::scenario::FieldStateEnum::BAR_TABLE);
    EXPECT_EQ(field.getField(2, 3).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(3, 3).getFieldState(), spy::scenario::FieldStateEnum::ROULETTE_TABLE);
    EXPECT_EQ(field.getField(4, 3).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(5, 3).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(6, 3).getFieldState(), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(field.getField(spy::util::Point(0, 4)).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(spy::util::Point(1, 4)).getFieldState(), spy::scenario::FieldStateEnum::BAR_SEAT);
    EXPECT_EQ(field.getField(spy::util::Point(2, 4)).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(spy::util::Point(3, 4)).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(spy::util::Point(4, 4)).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(spy::util::Point(5, 4)).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(spy::util::Point(6, 4)).getFieldState(), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(field.getField(spy::util::Point(0, 5)).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(spy::util::Point(1, 5)).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(spy::util::Point(2, 5)).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(spy::util::Point(3, 5)).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(spy::util::Point(4, 5)).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField(spy::util::Point(5, 5)).getFieldState(), spy::scenario::FieldStateEnum::SAFE);
    EXPECT_EQ(field.getField(spy::util::Point(6, 5)).getFieldState(), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(field.getField(spy::util::Point(0, 6)).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(spy::util::Point(1, 6)).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(spy::util::Point(2, 6)).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(spy::util::Point(3, 6)).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(spy::util::Point(4, 6)).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(spy::util::Point(5, 6)).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField(spy::util::Point(6, 6)).getFieldState(), spy::scenario::FieldStateEnum::WALL);
}

TEST(Scenario, FieldInsideTest) {
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

    spy::scenario::FieldMap field(decodedScenario);

    for (unsigned int y = 0; y < 7; y++) {
        for (unsigned int x = 0; x < 7; x++) {
            EXPECT_TRUE(field.isInside(spy::util::Point(x, y)));
        }
    }

    for (unsigned int i = 0; i < 7; i++) {
        EXPECT_FALSE(field.isInside(spy::util::Point(-1, i)));
        EXPECT_FALSE(field.isInside(spy::util::Point(7, i)));
        EXPECT_FALSE(field.isInside(spy::util::Point(i, -1)));
        EXPECT_FALSE(field.isInside(spy::util::Point(i, 7)));
    }
}

