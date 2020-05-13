/**
 * @file   scenarioTest.cpp
 * @author Dominik Authaler
 * @date   07.04.2020 (creation)
 * @brief  Unit tests for the Scenario classes.
 */

#include <gtest/gtest.h>
#include <datatypes/scenario/Scenario.hpp>
#include <datatypes/scenario/FieldMap.hpp>

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

    EXPECT_EQ(decodedScenario.getField({0, 4}), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField({1, 4}), spy::scenario::FieldStateEnum::BAR_SEAT);
    EXPECT_EQ(decodedScenario.getField({2, 4}), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField({3, 4}), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField({4, 4}), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField({5, 4}), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField({6, 4}), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(decodedScenario.getField({0, 5}), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField({1, 5}), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField({2, 5}), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField({3, 5}), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField({4, 5}), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(decodedScenario.getField({5, 5}), spy::scenario::FieldStateEnum::SAFE);
    EXPECT_EQ(decodedScenario.getField({6, 5}), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(decodedScenario.getField({0, 6}), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField({1, 6}), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField({2, 6}), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField({3, 6}), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField({4, 6}), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField({5, 6}), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(decodedScenario.getField({6, 6}), spy::scenario::FieldStateEnum::WALL);

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

    EXPECT_EQ(field.getField({0, 4}).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField({1, 4}).getFieldState(), spy::scenario::FieldStateEnum::BAR_SEAT);
    EXPECT_EQ(field.getField({2, 4}).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField({3, 4}).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField({4, 4}).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField({5, 4}).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField({6, 4}).getFieldState(), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(field.getField({0, 5}).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField({1, 5}).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField({2, 5}).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField({3, 5}).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField({4, 5}).getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(field.getField({5, 5}).getFieldState(), spy::scenario::FieldStateEnum::SAFE);
    EXPECT_EQ(field.getField({6, 5}).getFieldState(), spy::scenario::FieldStateEnum::WALL);

    EXPECT_EQ(field.getField({0, 6}).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField({1, 6}).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField({2, 6}).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField({3, 6}).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField({4, 6}).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField({5, 6}).getFieldState(), spy::scenario::FieldStateEnum::WALL);
    EXPECT_EQ(field.getField({6, 6}).getFieldState(), spy::scenario::FieldStateEnum::WALL);
}

TEST(Scenario, FieldMapSetters) {
    auto input = R"({ "scenario": [
		["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
        ]})"_json;

    spy::scenario::Scenario decodedScenario;
    EXPECT_NO_THROW(decodedScenario = input.get<spy::scenario::Scenario>());

    spy::scenario::FieldMap field(decodedScenario);

    spy::scenario::Field f(spy::scenario::FieldStateEnum::FREE);
    EXPECT_NO_THROW(field.setField(0, 0, f));
    EXPECT_EQ(field.getField({0, 0}).getFieldState(), spy::scenario::FieldStateEnum::FREE);

    EXPECT_NO_THROW(field.setField({0, 0}, f));
    EXPECT_EQ(field.getField({0, 0}).getFieldState(), spy::scenario::FieldStateEnum::FREE);

    EXPECT_ANY_THROW(field.setField({-1, 0}, f));
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

    for (int y = 0; y < 7; y++) {
        for (int x = 0; x < 7; x++) {
            EXPECT_TRUE(field.isInside({x, y}));
        }
    }

    for (int i = 0; i < 7; i++) {
        EXPECT_FALSE(field.isInside({-1, i}));
        EXPECT_FALSE(field.isInside({7, i}));
        EXPECT_FALSE(field.isInside({i, -1}));
        EXPECT_FALSE(field.isInside({i, 7}));
    }
}

TEST(Scenario, DimensionTests) {
    auto input = R"({ "scenario": [
		["WALL"],
		["WALL", "FIREPLACE"],
		["WALL", "FREE",      "FREE"],
		["WALL", "BAR_TABLE", "FREE", "ROULETTE_TABLE"],
		["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE"],
		["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE"],
		["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
	    ]})"_json;

    spy::scenario::Scenario decodedScenario;
    EXPECT_NO_THROW(decodedScenario = input.get<spy::scenario::Scenario>());

    EXPECT_EQ(decodedScenario.getNumberOfRows(), 7);
    EXPECT_EQ(decodedScenario.getRowLength(0), 1);
    EXPECT_EQ(decodedScenario.getRowLength(1), 2);
    EXPECT_EQ(decodedScenario.getRowLength(2), 3);
    EXPECT_EQ(decodedScenario.getRowLength(3), 4);
    EXPECT_EQ(decodedScenario.getRowLength(4), 5);
    EXPECT_EQ(decodedScenario.getRowLength(5), 6);
    EXPECT_EQ(decodedScenario.getRowLength(6), 7);
}

TEST(Scenario, ScenarioSetters) {
    auto input = R"({ "scenario": [
		["WALL"],
		["WALL", "FIREPLACE"],
		["WALL", "FREE",      "FREE"],
		["WALL", "BAR_TABLE", "FREE", "ROULETTE_TABLE"],
		["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE"],
		["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE"],
		["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
	    ]})"_json;

    spy::scenario::Scenario decodedScenario;
    EXPECT_NO_THROW(decodedScenario = input.get<spy::scenario::Scenario>());

    EXPECT_NO_THROW(decodedScenario.setField(0, 0, spy::scenario::FieldStateEnum::FREE));
    EXPECT_EQ(decodedScenario.getField(0, 0), spy::scenario::FieldStateEnum::FREE);

    EXPECT_NO_THROW(decodedScenario.setField({0, 1}, spy::scenario::FieldStateEnum::FREE));
    EXPECT_EQ(decodedScenario.getField({0, 1}), spy::scenario::FieldStateEnum::FREE);

    EXPECT_ANY_THROW(decodedScenario.setField(1, 0, spy::scenario::FieldStateEnum::FREE));
}

TEST(Scenario, EqualityOperator) {
    auto input1 = R"({ "scenario": [
		["WALL"],
		["WALL", "FIREPLACE"],
		["WALL", "FREE",      "FREE"],
		["WALL", "BAR_TABLE", "FREE", "ROULETTE_TABLE"],
		["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE"],
		["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE"],
		["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
	    ]})"_json;

    auto input2 = R"({ "scenario": [["WALL"]]})"_json;

    auto input3 = R"({ "scenario": [["WALL", "FREE"]]})"_json;

    spy::scenario::Scenario decodedScenario1;
    spy::scenario::Scenario decodedScenario2;
    spy::scenario::Scenario decodedScenario3;
    spy::scenario::Scenario decodedScenario4;
    EXPECT_NO_THROW(decodedScenario1 = input1.get<spy::scenario::Scenario>());
    EXPECT_NO_THROW(decodedScenario2 = input1.get<spy::scenario::Scenario>());
    EXPECT_NO_THROW(decodedScenario3 = input2.get<spy::scenario::Scenario>());
    EXPECT_NO_THROW(decodedScenario4 = input3.get<spy::scenario::Scenario>());

    EXPECT_TRUE(decodedScenario1 == decodedScenario2);
    EXPECT_FALSE(decodedScenario1 == decodedScenario3);
    EXPECT_FALSE(decodedScenario1 == decodedScenario4);
    EXPECT_FALSE(decodedScenario1 != decodedScenario2);
    EXPECT_TRUE(decodedScenario1 != decodedScenario3);
    EXPECT_TRUE(decodedScenario1 != decodedScenario4);

    decodedScenario1.setField(0, 0, spy::scenario::FieldStateEnum::FREE);

    EXPECT_FALSE(decodedScenario1 == decodedScenario2);
    EXPECT_TRUE(decodedScenario1 != decodedScenario2);


}

TEST(Scenario, FieldConstruction) {
    spy::scenario::Field f(spy::scenario::FieldStateEnum::FREE);
    EXPECT_EQ(f.getFieldState(), spy::scenario::FieldStateEnum::FREE);
    EXPECT_FALSE(f.isDestroyed().has_value());
    EXPECT_FALSE(f.isInverted().has_value());
    EXPECT_FALSE(f.getChipAmount().has_value());
    EXPECT_FALSE(f.getSafeIndex().has_value());
    EXPECT_FALSE(f.isUpdated().has_value());
    EXPECT_FALSE(f.getGadget().has_value());
    EXPECT_FALSE(f.isFoggy());

    EXPECT_ANY_THROW(f.setDestroyed(false));
    EXPECT_ANY_THROW(f.setInverted(false));
    EXPECT_ANY_THROW(f.setChipAmount(0));
    EXPECT_ANY_THROW(f.setSafeIndex(0));

    EXPECT_NO_THROW(f.setFieldState(spy::scenario::FieldStateEnum::ROULETTE_TABLE));
    EXPECT_EQ(f.getFieldState(), spy::scenario::FieldStateEnum::ROULETTE_TABLE);

    EXPECT_NO_THROW(f.setDestroyed(false));
    EXPECT_NO_THROW(f.setInverted(false));
    EXPECT_NO_THROW(f.setChipAmount(0));
    EXPECT_NO_THROW(f.setGadget(std::make_shared<spy::gadget::Gadget>()));
    EXPECT_ANY_THROW(f.setSafeIndex(0));
    EXPECT_NO_THROW(f.setFoggy(false));
    EXPECT_NO_THROW(f.setUpdated(true));

    EXPECT_TRUE(f.isDestroyed().has_value());
    EXPECT_FALSE(f.isDestroyed().value());
    EXPECT_TRUE(f.isInverted().has_value());
    EXPECT_FALSE(f.isInverted().value());
    EXPECT_TRUE(f.getChipAmount().has_value());
    EXPECT_EQ(f.getChipAmount().value(), 0);
    EXPECT_FALSE(f.getSafeIndex().has_value());
    EXPECT_TRUE(f.getGadget().has_value());
    EXPECT_FALSE(f.isFoggy());
    EXPECT_TRUE(f.isUpdated().has_value());
    EXPECT_TRUE(f.isUpdated().value());

    EXPECT_NO_THROW(f.setFieldState(spy::scenario::FieldStateEnum::SAFE));
    EXPECT_EQ(f.getFieldState(), spy::scenario::FieldStateEnum::SAFE);

    EXPECT_ANY_THROW(f.setDestroyed(false));
    EXPECT_ANY_THROW(f.setInverted(false));
    EXPECT_ANY_THROW(f.setChipAmount(0));
    EXPECT_NO_THROW(f.setSafeIndex(0));

    EXPECT_FALSE(f.isDestroyed().has_value());
    EXPECT_FALSE(f.isInverted().has_value());
    EXPECT_FALSE(f.getChipAmount().has_value());
    EXPECT_TRUE(f.getSafeIndex().has_value());
    EXPECT_EQ(f.getSafeIndex().value(), 0);
}

TEST(Scenario, FieldJsonConsistency) {
    auto input = R"({ "scenario": [["WALL", "FREE", "WALL"]]})"_json;

    spy::scenario::Scenario decodedScenario;
    EXPECT_NO_THROW(decodedScenario = input.get<spy::scenario::Scenario>());

    spy::scenario::FieldMap field(decodedScenario);
    nlohmann::json json = field;

    std::string jsonString = json.dump();

    auto parsedField = nlohmann::json::parse(jsonString).get<spy::scenario::FieldMap>();

    std::vector<std::vector<spy::scenario::Field>> map = parsedField.getMap();
    for (unsigned int y = 0; y < map.size(); y++) {
        for (unsigned int x = 0; x < map.at(y).size(); x++) {
            EXPECT_EQ(map.at(y).at(x).getFieldState(), decodedScenario.getField(x, y));
        }
    }
}