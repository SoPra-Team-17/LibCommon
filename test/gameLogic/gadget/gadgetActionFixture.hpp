/**
 * @file   gadgetActionFixture.hpp
 * @author Dominik Authaler
 * @date   29.04.2020 (creation)
 * @brief  Fixture for the gadget tests.
 */

#ifndef LIBCOMMON_GADGET_ACTION_FIXTURE_HPP
#define LIBCOMMON_GADGET_ACTION_FIXTURE_HPP

#include "scenario/Scenario.hpp"
#include "scenario/FieldMap.hpp"
#include "gameplay/State.hpp"
#include "character/Character.hpp"
#include "util/Point.hpp"

class GadgetActionTests : public ::testing::Test {
    protected:
        spy::util::UUID uuid1 = spy::util::UUID::generate();
        spy::util::UUID uuid2 = spy::util::UUID::generate();
        spy::util::UUID uuid3 = spy::util::UUID::generate();
        spy::util::UUID uuid4 = spy::util::UUID::generate();
        spy::util::UUID uuid5 = spy::util::UUID::generate();
        spy::util::UUID uuid6 = spy::util::UUID::generate();
        spy::util::UUID uuid7 = spy::util::UUID::generate();

        nlohmann::json input = R"({ "scenario": [
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"],
            ["WALL", "FIREPLACE", "WALL", "BAR_TABLE",      "BAR_SEAT", "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_TABLE", "WALL", "ROULETTE_TABLE", "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE",     "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE", "WALL"],
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "FREE"]
            ]})"_json;

        spy::scenario::Scenario decodedScenario = input.get<spy::scenario::Scenario>();

        spy::scenario::FieldMap field{decodedScenario};

        spy::character::CharacterSet characters = {{uuid1, "dummy"}, {uuid2, "dummy"},
                                                   {uuid3, "dummy"}, {uuid4, "dummy"},
                                                   {uuid5, "dummy"}, {uuid6, "dummy"},
                                                   {uuid7, "dummy"}};

        spy::gameplay::State state{0, field, {}, characters, std::nullopt, std::nullopt};
};

#endif //LIBCOMMON_GADGET_ACTION_FIXTURE_HPP
