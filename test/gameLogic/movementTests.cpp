/**
 * @file   movementTests.cpp
 * @author Dominik Authaler
 * @date   24.04.2020 (creation)
 * @brief  Unit tests for the execution of game operations.
 */

#include <gtest/gtest.h>
#include "scenario/Scenario.hpp"
#include "scenario/FieldMap.hpp"
#include "gameplay/State.hpp"
#include "character/Character.hpp"

static auto input = R"({ "scenario": [
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"],
            ["WALL", "FIREPLACE", "WALL", "BAR_TABLE",      "BAR_SEAT", "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_TABLE", "WALL", "ROULETTE_TABLE", "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE",     "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE", "WALL"],
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
            ]})"_json;

TEST(MovementOperation, Validation) {
    using spy::scenario::Scenario;
    using spy::scenario::FieldMap;
    using spy::character::Character;
    using spy::character::CharacterSet;
    using spy::util::UUID;
    using spy::gameplay::Movement;
    using spy::gameplay::State;

    Scenario decodedScenario;
    decodedScenario = input.get<Scenario>();

    FieldMap field(decodedScenario);

    UUID uuid = UUID::generate();

    Character c(uuid, "dummy");
    c.setCoordinates({1, 2});
    CharacterSet characters = {c};

    Movement move1(false, {3, 2}, uuid, {1, 2});
    Movement move2(false, {2, 2}, uuid, {1, 2});
    Movement move3(false, {3, 2}, UUID(), {1, 2});
    Movement move4(false, {1, 1}, UUID(), {1, 2});

    State state(0, field, {}, characters, std::nullopt, std::nullopt);

    EXPECT_FALSE(state.isMovementValid(move1));
    EXPECT_TRUE(state.isMovementValid(move2));
    EXPECT_FALSE(state.isMovementValid(move3));
    EXPECT_FALSE(state.isMovementValid(move4));
}

TEST(MovementOperation, PerformValidate) {
    using spy::scenario::Scenario;
    using spy::scenario::FieldMap;
    using spy::character::Character;
    using spy::character::CharacterSet;
    using spy::util::UUID;
    using spy::gameplay::Movement;
    using spy::gameplay::State;

    Scenario decodedScenario;
    decodedScenario = input.get<Scenario>();

    FieldMap field(decodedScenario);

    UUID uuid1 = UUID::generate();
    UUID uuid2 = UUID::generate();

    Character c1(uuid1, "dummy");
    Character c2(uuid2, "dummy");

    c1.setCoordinates({1, 2});
    c2.setCoordinates({1, 5});
    CharacterSet characters = {c1, c2};

    Movement move1(false, {1, 1}, uuid1, {1, 2});
    Movement move2(false, {1, 3}, uuid1, {1, 2});
    Movement move3(false, {3, 3}, uuid1, {3, 2});
    Movement move4(false, {5, 5}, uuid1, {4, 5});
    Movement move5(false, {0, 2}, uuid1, {1, 2});
    Movement move6(false, {1, 4}, uuid2, {1, 5});
    Movement move7(false, {2, 2}, uuid1, {1, 2});
    Movement move8(false, {1, 4}, uuid1, {1, 5});
    Movement move9(false, {2, 2}, uuid2, {1, 2});

    State state(0, field, {}, characters, std::nullopt, std::nullopt);

    EXPECT_FALSE(state.performMovement(move1));
    EXPECT_FALSE(state.performMovement(move2));
    EXPECT_FALSE(state.performMovement(move3));
    EXPECT_FALSE(state.performMovement(move4));
    EXPECT_FALSE(state.performMovement(move5));

    EXPECT_TRUE(state.performMovement(move6));
    EXPECT_TRUE(state.performMovement(move7));

    EXPECT_FALSE(state.performMovement(move8));
    EXPECT_FALSE(state.performMovement(move9));
}

