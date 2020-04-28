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
#include "util/Point.hpp"
#include "datatypes/validation/ActionValidator.hpp"

class MovementOperation : public ::testing::Test {
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

        spy::gadget::Gadget g1{spy::gadget::GadgetEnum::BOWLER_BLADE};
        spy::gadget::Gadget g2{spy::gadget::GadgetEnum::CHICKEN_FEED};
        spy::gadget::Gadget g3{spy::gadget::GadgetEnum::FOG_TIN};
        spy::gadget::Gadget g4{spy::gadget::GadgetEnum::GAS_GLOSS};
        spy::gadget::Gadget g5{spy::gadget::GadgetEnum::DIAMOND_COLLAR};

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

        spy::character::CharacterSet characters = {c1, c2, c3, c4, c5};

        spy::gameplay::State state{0, field, {}, characters, std::nullopt, std::nullopt};
};

TEST_F(MovementOperation, isMovementValid) {
    using spy::util::UUID;
    using spy::gameplay::ActionValidator;
    using spy::gameplay::Movement;

    state.getCharacters().getByUUID(uuid1)->setCoordinates({1, 2});

    Movement move1(false, {3, 2}, uuid1, {1, 2});
    Movement move2(false, {2, 2}, uuid1, {1, 2});
    Movement move3(false, {3, 2}, UUID(), {1, 2});
    Movement move4(false, {1, 1}, UUID(), {1, 2});
    Movement move5(false, {2, 2}, uuid1, {1, 3});

    EXPECT_FALSE(ActionValidator::validate(state, move1));
    EXPECT_TRUE(ActionValidator::validate(state, move2));
    EXPECT_FALSE(ActionValidator::validate(state, move3));
    EXPECT_FALSE(ActionValidator::validate(state, move4));
    EXPECT_FALSE(ActionValidator::validate(state, move5));
}

TEST_F(MovementOperation, PerformValidate) {
    using spy::scenario::Scenario;
    using spy::scenario::FieldMap;
    using spy::character::Character;
    using spy::character::CharacterSet;
    using spy::util::UUID;
    using spy::gameplay::Movement;
    using spy::gameplay::State;

    state.getCharacters().getByUUID(uuid1)->setCoordinates({1, 2});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({1, 5});

    Movement move1(false, {1, 1}, uuid1, {1, 2});
    Movement move2(false, {1, 3}, uuid1, {1, 2});
    Movement move3(false, {3, 3}, uuid1, {3, 2});
    Movement move4(false, {5, 5}, uuid1, {4, 5});
    Movement move5(false, {0, 2}, uuid1, {1, 2});
    Movement move6(false, {1, 4}, uuid2, {1, 5});
    Movement move7(false, {2, 2}, uuid1, {1, 2});
    Movement move8(false, {1, 4}, uuid1, {1, 5});
    Movement move9(false, {2, 2}, uuid2, {1, 2});

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

TEST_F(MovementOperation, Movement) {
    using spy::gameplay::Movement;
    using spy::util::Point;

    state.getCharacters().getByUUID(uuid1)->setCoordinates({1, 2});

    Movement move1(false, {2, 2}, uuid1, {1, 2});
    Movement move2(false, {3, 2}, uuid1, {2, 2});
    Movement move3(false, {4, 3}, uuid1, {3, 2});
    Movement move4(false, {4, 4}, uuid1, {4, 3});
    Movement move5(false, {5, 3}, uuid1, {4, 4});
    Movement move6(false, {6, 3}, uuid1, {5, 3});

    ASSERT_TRUE(state.performMovement(move1));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{2, 2}));

    ASSERT_TRUE(state.performMovement(move2));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{3, 2}));

    ASSERT_TRUE(state.performMovement(move3));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{4, 3}));

    ASSERT_TRUE(state.performMovement(move4));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{4, 4}));

    ASSERT_TRUE(state.performMovement(move5));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{5, 3}));

    ASSERT_FALSE(state.performMovement(move6));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{5, 3}));
}

TEST_F(MovementOperation, MovementSwap) {
    using spy::gameplay::Movement;
    using spy::util::Point;

    state.getCharacters().getByUUID(uuid1)->setCoordinates({1, 2});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({2, 2});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({3, 2});
    state.getCharacters().getByUUID(uuid4)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({4, 4});

    Movement move1(false, {2, 2}, uuid1, {1, 2});
    Movement move2(false, {3, 2}, uuid1, {2, 2});
    Movement move3(false, {4, 3}, uuid1, {3, 2});
    Movement move4(false, {4, 4}, uuid1, {4, 3});
    Movement move5(false, {5, 3}, uuid1, {4, 4});
    Movement move6(false, {6, 3}, uuid1, {5, 3});

    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 4}));

    ASSERT_TRUE(state.performMovement(move1));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 4}));

    ASSERT_TRUE(state.performMovement(move2));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 4}));

    ASSERT_TRUE(state.performMovement(move3));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 4}));

    ASSERT_TRUE(state.performMovement(move4));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{4, 4}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 3}));

    ASSERT_TRUE(state.performMovement(move5));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{5, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 3}));

    ASSERT_FALSE(state.performMovement(move6));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (Point{5, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (Point{4, 3}));
}

TEST_F(MovementOperation, MovementGadget) {
    using spy::gameplay::Movement;

    state.getMap().getField({2, 2}).setGadget(g1);
    state.getMap().getField({3, 2}).setGadget(g2);
    state.getMap().getField({4, 3}).setGadget(g3);
    state.getMap().getField({4, 4}).setGadget(g4);
    state.getMap().getField({5, 3}).setGadget(g5);

    state.getCharacters().getByUUID(uuid1)->setCoordinates({1, 2});

    Movement move1(false, {2, 2}, uuid1, {1, 2});
    Movement move2(false, {3, 2}, uuid1, {2, 2});
    Movement move3(false, {4, 3}, uuid1, {3, 2});
    Movement move4(false, {4, 4}, uuid1, {4, 3});
    Movement move5(false, {5, 3}, uuid1, {4, 4});
    Movement move6(false, {6, 3}, uuid1, {5, 3});

    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getGadgets().size(), 0);
    ASSERT_EQ(state.getMap().getField({2, 2}).getGadget()->getType(), spy::gadget::GadgetEnum::BOWLER_BLADE);
    ASSERT_EQ(state.getMap().getField({3, 2}).getGadget()->getType(), spy::gadget::GadgetEnum::CHICKEN_FEED);
    ASSERT_EQ(state.getMap().getField({4, 3}).getGadget()->getType(), spy::gadget::GadgetEnum::FOG_TIN);
    ASSERT_EQ(state.getMap().getField({4, 4}).getGadget()->getType(), spy::gadget::GadgetEnum::GAS_GLOSS);
    ASSERT_EQ(state.getMap().getField({5, 3}).getGadget()->getType(), spy::gadget::GadgetEnum::DIAMOND_COLLAR);

    ASSERT_TRUE(state.performMovement(move1));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{2, 2}));
    ASSERT_FALSE(state.getMap().getField({2, 2}).getGadget().has_value());
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getGadgets().size(), 1);

    ASSERT_NE(std::find(state.getCharacters().getByUUID(uuid1)->getGadgets().begin(),
                        state.getCharacters().getByUUID(uuid1)->getGadgets().end(), g1),
              state.getCharacters().getByUUID(uuid1)->getGadgets().end());
    ASSERT_EQ(state.getMap().getField({3, 2}).getGadget()->getType(), spy::gadget::GadgetEnum::CHICKEN_FEED);
    ASSERT_EQ(state.getMap().getField({4, 3}).getGadget()->getType(), spy::gadget::GadgetEnum::FOG_TIN);
    ASSERT_EQ(state.getMap().getField({4, 4}).getGadget()->getType(), spy::gadget::GadgetEnum::GAS_GLOSS);
    ASSERT_EQ(state.getMap().getField({5, 3}).getGadget()->getType(), spy::gadget::GadgetEnum::DIAMOND_COLLAR);

    ASSERT_TRUE(state.performMovement(move2));
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
    ASSERT_EQ(state.getMap().getField({4, 3}).getGadget()->getType(), spy::gadget::GadgetEnum::FOG_TIN);
    ASSERT_EQ(state.getMap().getField({4, 4}).getGadget()->getType(), spy::gadget::GadgetEnum::GAS_GLOSS);
    ASSERT_EQ(state.getMap().getField({5, 3}).getGadget()->getType(), spy::gadget::GadgetEnum::DIAMOND_COLLAR);

    ASSERT_TRUE(state.performMovement(move3));
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
    ASSERT_EQ(state.getMap().getField({4, 4}).getGadget()->getType(), spy::gadget::GadgetEnum::GAS_GLOSS);
    ASSERT_EQ(state.getMap().getField({5, 3}).getGadget()->getType(), spy::gadget::GadgetEnum::DIAMOND_COLLAR);

    ASSERT_TRUE(state.performMovement(move4));
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
    ASSERT_EQ(state.getMap().getField({5, 3}).getGadget()->getType(), spy::gadget::GadgetEnum::DIAMOND_COLLAR);

    ASSERT_TRUE(state.performMovement(move5));
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

    ASSERT_FALSE(state.performMovement(move6));
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

