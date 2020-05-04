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
#include "character/CharacterSet.hpp"
#include "util/Point.hpp"
#include "matchconfig/MatchConfig.hpp"

class GadgetActionTests : public ::testing::Test {
    public:
        GadgetActionTests() {
            for (auto it = state.getCharacters().begin(); it != state.getCharacters().end(); it++) {
                it->setActionPoints(1);
                it->setMovePoints(1);
            }
        }

    protected:
        spy::util::UUID uuid1 = spy::util::UUID::generate();
        spy::util::UUID uuid2 = spy::util::UUID::generate();
        spy::util::UUID uuid3 = spy::util::UUID::generate();
        spy::util::UUID uuid4 = spy::util::UUID::generate();
        spy::util::UUID uuid5 = spy::util::UUID::generate();
        spy::util::UUID uuid6 = spy::util::UUID::generate();
        spy::util::UUID uuid7 = spy::util::UUID::generate();

        nlohmann::json scenarioInput = R"({ "scenario": [
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"],
            ["WALL", "FIREPLACE", "WALL", "BAR_TABLE",      "BAR_SEAT", "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_TABLE", "WALL", "ROULETTE_TABLE", "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE",     "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE", "WALL"],
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "FREE"]
            ]})"_json;

        nlohmann::json matchConfigInput = R"({
            "moledieRange": 1,
            "bowlerBladeRange": 1,
            "bowlerBladeHitChance": 0.25,
            "bowlerBladeDamage": 4,
            "laserCompactHitChance": 0.125,
            "rocketPenDamage": 2,
            "gasGlossDamage": 6,
            "mothballPouchRange": 2,
            "mothballPouchDamage": 1,
            "fogTinRange": 2,
            "grappleRange": 3,
            "grappleHitChance": 0.35,
            "wiretapWithEarplugsFailChance": 0.64,
            "mirrorSwapChance": 0.35,
            "cocktailDodgeChance": 0.25,
            "cocktailHp": 6,
            "spySuccessChance": 0.65,
            "babysitterSuccessChance": 0.25,
            "honeyTrapSuccessChance": 0.35,
            "observationSuccessChance": 0.12,
            "chipsToIpFactor": 12,
            "roundLimit": 15,
            "turnPhaseLimit": 6,
            "catIp": 8,
            "strikeMaximum": 4,
            "pauseLimit": 320,
            "reconnectLimit": 20
        })"_json;

        spy::scenario::Scenario decodedScenario = scenarioInput.get<spy::scenario::Scenario>();

        spy::scenario::FieldMap field{decodedScenario};

        spy::character::CharacterSet characters = {{uuid1, "dummy"},
                                                   {uuid2, "dummy"},
                                                   {uuid3, "dummy"},
                                                   {uuid4, "dummy"},
                                                   {uuid5, "dummy"},
                                                   {uuid6, "dummy"},
                                                   {uuid7, "dummy"}};

        spy::gameplay::State state{0, field, {}, characters, std::nullopt, std::nullopt};

        spy::MatchConfig config = matchConfigInput.get<spy::MatchConfig>();
};

#endif //LIBCOMMON_GADGET_ACTION_FIXTURE_HPP
