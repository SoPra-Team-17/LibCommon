/**
 * @file   operationTests.cpp
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

TEST(Operations, MovementOperation) {
    using spy::scenario::Scenario;
    using spy::scenario::FieldMap;
    using spy::character::Character;
    using spy::util::UUID;
    using spy::gameplay::Movement;
    using spy::gameplay::State;

    Scenario decodedScenario;
    decodedScenario = input.get<Scenario>();

    FieldMap field(decodedScenario);

    Character::Set characters;

    UUID uuid = UUID::generate();

    characters.emplace(uuid, "dummy");

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

