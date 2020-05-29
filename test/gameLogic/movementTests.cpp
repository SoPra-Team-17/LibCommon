/**
 * @file   movementTests.cpp
 * @author Dominik Authaler
 * @date   24.04.2020 (creation)
 * @brief  Unit tests for the execution of game operations.
 */

#include <gtest/gtest.h>
#include "datatypes/scenario/Scenario.hpp"
#include "datatypes/scenario/FieldMap.hpp"
#include "datatypes/gameplay/State.hpp"
#include "datatypes/character/Character.hpp"
#include "util/Point.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "gameLogic/execution/ActionExecutor.hpp"

class MovementOperation : public ::testing::Test {
    using GadgetPtr = std::shared_ptr<spy::gadget::Gadget>;

    public:
        MovementOperation() {
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

        spy::character::Character c1{uuid1, "dummy"};
        spy::character::Character c2{uuid2, "dummy"};
        spy::character::Character c3{uuid3, "dummy"};
        spy::character::Character c4{uuid4, "dummy"};
        spy::character::Character c5{uuid5, "dummy"};

        GadgetPtr g1 = std::make_shared<spy::gadget::Gadget>(spy::gadget::GadgetEnum::BOWLER_BLADE);
        GadgetPtr g2 = std::make_shared<spy::gadget::Gadget>(spy::gadget::GadgetEnum::CHICKEN_FEED);
        GadgetPtr g3 = std::make_shared<spy::gadget::Gadget>(spy::gadget::GadgetEnum::FOG_TIN);
        GadgetPtr g4 = std::make_shared<spy::gadget::Gadget>(spy::gadget::GadgetEnum::GAS_GLOSS);
        GadgetPtr g5 = std::make_shared<spy::gadget::Gadget>(spy::gadget::GadgetEnum::DIAMOND_COLLAR);

        nlohmann::json scenarioInput = R"({ "scenario": [
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"],
            ["WALL", "FIREPLACE", "WALL", "BAR_TABLE",      "BAR_SEAT", "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_TABLE", "WALL", "ROULETTE_TABLE", "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE",     "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE", "WALL"],
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
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
            "secretToIpFactor": 9,
            "minChipsRoulette": 0,
            "maxChipsRoulette": 6,
            "roundLimit": 15,
            "turnPhaseLimit": 6,
            "catIp": 8,
            "strikeMaximum": 4,
            "pauseLimit": 320,
            "reconnectLimit": 20
        })"_json;

        spy::scenario::Scenario decodedScenario = scenarioInput.get<spy::scenario::Scenario>();

        spy::scenario::FieldMap field{decodedScenario};

        spy::character::CharacterSet characters = {c1, c2, c3, c4, c5};

        spy::gameplay::State state{0, field, {}, characters, std::nullopt, std::nullopt};

        spy::MatchConfig config = matchConfigInput.get<spy::MatchConfig>();
};

TEST_F(MovementOperation, isMovementValid) {
    using spy::scenario::Scenario;
    using spy::scenario::FieldMap;
    using spy::character::Character;
    using spy::character::CharacterSet;
    using spy::util::UUID;
    using spy::gameplay::Movement;
    using spy::gameplay::State;
    using spy::gameplay::ActionValidator;

    state.getCharacters().getByUUID(uuid1)->setCoordinates({1, 2});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({1, 5});

    auto move1 = std::make_shared<Movement>(Movement(false, {1, 1}, uuid1, {1, 2}));
    auto move2 = std::make_shared<Movement>(Movement(false, {1, 3}, uuid1, {1, 2}));
    auto move3 = std::make_shared<Movement>(Movement(false, {3, 3}, uuid1, {3, 2}));
    auto move4 = std::make_shared<Movement>(Movement(false, {5, 5}, uuid1, {4, 5}));
    auto move5 = std::make_shared<Movement>(Movement(false, {0, 2}, uuid1, {1, 2}));
    auto move6 = std::make_shared<Movement>(Movement(false, {1, 4}, uuid2, {1, 5}));
    auto move7 = std::make_shared<Movement>(Movement(false, {2, 2}, uuid1, {1, 2}));
    auto move8 = std::make_shared<Movement>(Movement(false, {1, 4}, uuid1, {1, 5}));
    auto move9 = std::make_shared<Movement>(Movement(false, {2, 2}, uuid2, {1, 2}));

    EXPECT_FALSE(ActionValidator::validate(state, move1, config));
    EXPECT_FALSE(ActionValidator::validate(state, move2, config));
    EXPECT_FALSE(ActionValidator::validate(state, move3, config));
    EXPECT_FALSE(ActionValidator::validate(state, move4, config));
    EXPECT_FALSE(ActionValidator::validate(state, move5, config));

    EXPECT_TRUE(ActionValidator::validate(state, move6, config));
    EXPECT_TRUE(ActionValidator::validate(state, move7, config));

    EXPECT_FALSE(ActionValidator::validate(state, move8, config));
    EXPECT_FALSE(ActionValidator::validate(state, move9, config));
}

TEST_F(MovementOperation, Movement) {
    using spy::gameplay::Movement;
    using spy::util::Point;
    using spy::gameplay::ActionExecutor;

    state.getCharacters().getByUUID(uuid1)->setCoordinates({1, 2});

    auto move1 = std::make_shared<Movement>(Movement(false, {2, 2}, uuid1, {1, 2}));
    auto move2 = std::make_shared<Movement>(Movement(false, {3, 2}, uuid1, {2, 2}));
    auto move3 = std::make_shared<Movement>(Movement(false, {4, 3}, uuid1, {3, 2}));
    auto move4 = std::make_shared<Movement>(Movement(false, {4, 4}, uuid1, {4, 3}));
    auto move5 = std::make_shared<Movement>(Movement(false, {5, 3}, uuid1, {4, 4}));

    ASSERT_TRUE(ActionExecutor::execute(state, move1, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{2, 2}));

    ASSERT_TRUE(ActionExecutor::execute(state, move2, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{3, 2}));

    ASSERT_TRUE(ActionExecutor::execute(state, move3, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{4, 3}));

    ASSERT_TRUE(ActionExecutor::execute(state, move4, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{4, 4}));

    ASSERT_TRUE(ActionExecutor::execute(state, move5, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{5, 3}));
}

TEST_F(MovementOperation, MovementSwap) {
    using spy::gameplay::Movement;
    using spy::util::Point;
    using spy::gameplay::ActionExecutor;

    state.getCharacters().getByUUID(uuid1)->setCoordinates({1, 2});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({2, 2});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({3, 2});
    state.getCharacters().getByUUID(uuid4)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({4, 4});

    auto move1 = std::make_shared<Movement>(Movement(false, {2, 2}, uuid1, {1, 2}));
    auto move2 = std::make_shared<Movement>(Movement(false, {3, 2}, uuid1, {2, 2}));
    auto move3 = std::make_shared<Movement>(Movement(false, {4, 3}, uuid1, {3, 2}));
    auto move4 = std::make_shared<Movement>(Movement(false, {4, 4}, uuid1, {4, 3}));
    auto move5 = std::make_shared<Movement>(Movement(false, {5, 3}, uuid1, {4, 4}));
    auto move6 = std::make_shared<Movement>(Movement(false, {6, 3}, uuid1, {5, 3}));

    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 4}));

    ASSERT_TRUE(ActionExecutor::execute(state, move1, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 4}));

    ASSERT_TRUE(ActionExecutor::execute(state, move2, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 4}));

    ASSERT_TRUE(ActionExecutor::execute(state, move3, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 4}));

    ASSERT_TRUE(ActionExecutor::execute(state, move4, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{4, 4}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 3}));

    ASSERT_TRUE(ActionExecutor::execute(state, move5, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{5, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 3}));
}

TEST_F(MovementOperation, MovementGadget) {
    using spy::gameplay::Movement;
    using spy::gameplay::ActionExecutor;

    state.getMap().getField({2, 2}).setGadget(g1);
    state.getMap().getField({3, 2}).setGadget(g2);
    state.getMap().getField({4, 3}).setGadget(g3);
    state.getMap().getField({4, 4}).setGadget(g4);
    state.getMap().getField({5, 3}).setGadget(g5);

    state.getCharacters().getByUUID(uuid1)->setCoordinates({1, 2});

    auto move1 = std::make_shared<Movement>(Movement(false, {2, 2}, uuid1, {1, 2}));
    auto move2 = std::make_shared<Movement>(Movement(false, {3, 2}, uuid1, {2, 2}));
    auto move3 = std::make_shared<Movement>(Movement(false, {4, 3}, uuid1, {3, 2}));
    auto move4 = std::make_shared<Movement>(Movement(false, {4, 4}, uuid1, {4, 3}));
    auto move5 = std::make_shared<Movement>(Movement(false, {5, 3}, uuid1, {4, 4}));

    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getGadgets().size(), 0);
    ASSERT_EQ(state.getMap().getField({2, 2}).getGadget().value()->getType(), spy::gadget::GadgetEnum::BOWLER_BLADE);
    ASSERT_EQ(state.getMap().getField({3, 2}).getGadget().value()->getType(), spy::gadget::GadgetEnum::CHICKEN_FEED);
    ASSERT_EQ(state.getMap().getField({4, 3}).getGadget().value()->getType(), spy::gadget::GadgetEnum::FOG_TIN);
    ASSERT_EQ(state.getMap().getField({4, 4}).getGadget().value()->getType(), spy::gadget::GadgetEnum::GAS_GLOSS);
    ASSERT_EQ(state.getMap().getField({5, 3}).getGadget().value()->getType(), spy::gadget::GadgetEnum::DIAMOND_COLLAR);

    ASSERT_TRUE(ActionExecutor::execute(state, move1, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{2, 2}));
    ASSERT_FALSE(state.getMap().getField({2, 2}).getGadget().has_value());
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getGadgets().size(), 1);

    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g1),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_EQ(state.getMap().getField({3, 2}).getGadget().value()->getType(), spy::gadget::GadgetEnum::CHICKEN_FEED);
    ASSERT_EQ(state.getMap().getField({4, 3}).getGadget().value()->getType(), spy::gadget::GadgetEnum::FOG_TIN);
    ASSERT_EQ(state.getMap().getField({4, 4}).getGadget().value()->getType(), spy::gadget::GadgetEnum::GAS_GLOSS);
    ASSERT_EQ(state.getMap().getField({5, 3}).getGadget().value()->getType(), spy::gadget::GadgetEnum::DIAMOND_COLLAR);

    ASSERT_TRUE(ActionExecutor::execute(state, move2, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{3, 2}));
    ASSERT_FALSE(state.getMap().getField({2, 2}).getGadget().has_value());
    ASSERT_FALSE(state.getMap().getField({3, 2}).getGadget().has_value());
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getGadgets().size(), 2);
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g1),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g2),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_EQ(state.getMap().getField({4, 3}).getGadget().value()->getType(), spy::gadget::GadgetEnum::FOG_TIN);
    ASSERT_EQ(state.getMap().getField({4, 4}).getGadget().value()->getType(), spy::gadget::GadgetEnum::GAS_GLOSS);
    ASSERT_EQ(state.getMap().getField({5, 3}).getGadget().value()->getType(), spy::gadget::GadgetEnum::DIAMOND_COLLAR);

    ASSERT_TRUE(ActionExecutor::execute(state, move3, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{4, 3}));
    EXPECT_FALSE(state.getMap().getField({2, 2}).getGadget().has_value());
    EXPECT_FALSE(state.getMap().getField({3, 2}).getGadget().has_value());
    EXPECT_FALSE(state.getMap().getField({4, 3}).getGadget().has_value());
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getGadgets().size(), 3);
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g1),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g2),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g3),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_EQ(state.getMap().getField({4, 4}).getGadget().value()->getType(), spy::gadget::GadgetEnum::GAS_GLOSS);
    ASSERT_EQ(state.getMap().getField({5, 3}).getGadget().value()->getType(), spy::gadget::GadgetEnum::DIAMOND_COLLAR);

    ASSERT_TRUE(ActionExecutor::execute(state, move4, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{4, 4}));
    EXPECT_FALSE(state.getMap().getField({2, 2}).getGadget().has_value());
    EXPECT_FALSE(state.getMap().getField({3, 2}).getGadget().has_value());
    EXPECT_FALSE(state.getMap().getField({4, 3}).getGadget().has_value());
    EXPECT_FALSE(state.getMap().getField({4, 4}).getGadget().has_value());
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getGadgets().size(), 4);
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g1),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g2),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g3),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g4),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_EQ(state.getMap().getField({5, 3}).getGadget().value()->getType(), spy::gadget::GadgetEnum::DIAMOND_COLLAR);

    ASSERT_TRUE(ActionExecutor::execute(state, move5, config));
    ASSERT_FALSE(state.getMap().getField({2, 2}).getGadget().has_value());
    ASSERT_FALSE(state.getMap().getField({3, 2}).getGadget().has_value());
    ASSERT_FALSE(state.getMap().getField({4, 3}).getGadget().has_value());
    ASSERT_FALSE(state.getMap().getField({4, 4}).getGadget().has_value());
    ASSERT_FALSE(state.getMap().getField({5, 3}).getGadget().has_value());
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getGadgets().size(), 5);
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g1),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g2),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g3),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g4),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g5),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
}

TEST_F(MovementOperation, MovementCatJanitor) {
    using spy::gameplay::Movement;
    using spy::gameplay::ActionExecutor;
    using spy::util::Point;

    state.getCharacters().getByUUID(uuid1)->setCoordinates({1, 2});
    state.setCatCoordinates(Point{2, 2});
    state.setJanitorCoordinates(Point{3, 2});

    auto move1 = std::make_shared<Movement>(Movement(false, {2, 2}, uuid1, {1, 2}));
    auto move2 = std::make_shared<Movement>(Movement(false, {3, 2}, uuid1, {2, 2}));

    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCatCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getJanitorCoordinates().value(), (Point{3, 2}));

    ASSERT_TRUE(ActionExecutor::execute(state, move1, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCatCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getJanitorCoordinates().value(), (Point{3, 2}));

    ASSERT_TRUE(ActionExecutor::execute(state, move2, config));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCatCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getJanitorCoordinates().value(), (Point{2, 2}));
}

