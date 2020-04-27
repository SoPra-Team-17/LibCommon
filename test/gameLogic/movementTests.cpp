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

static auto input = R"({ "scenario": [
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"],
            ["WALL", "FIREPLACE", "WALL", "BAR_TABLE",      "BAR_SEAT", "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_TABLE", "WALL", "ROULETTE_TABLE", "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE",     "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE", "WALL"],
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
            ]})"_json;

TEST(MovementOperation, isMovementValid) {
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

TEST(MovementOperation, Movement) {
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

    Character c1(uuid, "dummy");

    c1.setCoordinates({1, 2});
    CharacterSet characters = {c1};

    Movement move1(false, {2, 2}, uuid, {1, 2});
    Movement move2(false, {3, 2}, uuid, {2, 2});
    Movement move3(false, {4, 3}, uuid, {3, 2});
    Movement move4(false, {4, 4}, uuid, {4, 3});
    Movement move5(false, {5, 3}, uuid, {4, 4});
    Movement move6(false, {6, 3}, uuid, {5, 3});

    State state(0, field, {}, characters, std::nullopt, std::nullopt);

    ASSERT_TRUE(state.performMovement(move1));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid)->getCoordinates().value(), (spy::util::Point{2, 2}));

    ASSERT_TRUE(state.performMovement(move2));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid)->getCoordinates().value(), (spy::util::Point{3, 2}));

    ASSERT_TRUE(state.performMovement(move3));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid)->getCoordinates().value(), (spy::util::Point{4, 3}));

    ASSERT_TRUE(state.performMovement(move4));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid)->getCoordinates().value(), (spy::util::Point{4, 4}));

    ASSERT_TRUE(state.performMovement(move5));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid)->getCoordinates().value(), (spy::util::Point{5, 3}));

    ASSERT_FALSE(state.performMovement(move6));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid)->getCoordinates().value(), (spy::util::Point{5, 3}));
}

TEST(MovementOperation, MovementSwap) {
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
    UUID uuid3 = UUID::generate();
    UUID uuid4 = UUID::generate();
    UUID uuid5 = UUID::generate();

    Character c1(uuid1, "dummy");
    Character c2(uuid2, "dummy");
    Character c3(uuid3, "dummy");
    Character c4(uuid4, "dummy");
    Character c5(uuid5, "dummy");

    c1.setCoordinates({1, 2});
    c2.setCoordinates({2, 2});
    c3.setCoordinates({3, 2});
    c4.setCoordinates({4, 3});
    c5.setCoordinates({4, 4});

    CharacterSet characters = {c1, c2, c3, c4, c5};

    Movement move1(false, {2, 2}, uuid1, {1, 2});
    Movement move2(false, {3, 2}, uuid1, {2, 2});
    Movement move3(false, {4, 3}, uuid1, {3, 2});
    Movement move4(false, {4, 4}, uuid1, {4, 3});
    Movement move5(false, {5, 3}, uuid1, {4, 4});
    Movement move6(false, {6, 3}, uuid1, {5, 3});

    State state(0, field, {}, characters, std::nullopt, std::nullopt);

    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (spy::util::Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (spy::util::Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (spy::util::Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (spy::util::Point{4, 4}));

    ASSERT_TRUE(state.performMovement(move1));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (spy::util::Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (spy::util::Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (spy::util::Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (spy::util::Point{4, 4}));

    ASSERT_TRUE(state.performMovement(move2));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (spy::util::Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (spy::util::Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (spy::util::Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (spy::util::Point{4, 4}));

    ASSERT_TRUE(state.performMovement(move3));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{4, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (spy::util::Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (spy::util::Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (spy::util::Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (spy::util::Point{4, 4}));

    ASSERT_TRUE(state.performMovement(move4));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{4, 4}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (spy::util::Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (spy::util::Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (spy::util::Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (spy::util::Point{4, 3}));

    ASSERT_TRUE(state.performMovement(move5));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{5, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (spy::util::Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (spy::util::Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (spy::util::Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (spy::util::Point{4, 3}));

    ASSERT_FALSE(state.performMovement(move6));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid1)->getCoordinates().value(), (spy::util::Point{5, 3}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid2)->getCoordinates().value(), (spy::util::Point{1, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid3)->getCoordinates().value(), (spy::util::Point{2, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid4)->getCoordinates().value(), (spy::util::Point{3, 2}));
    ASSERT_EQ(state.getCharacters().getByUUID(uuid5)->getCoordinates().value(), (spy::util::Point{4, 3}));
}

TEST(MovementOperation, MovementGadget) {
    using spy::scenario::Scenario;
    using spy::scenario::FieldMap;
    using spy::character::Character;
    using spy::character::CharacterSet;
    using spy::util::UUID;
    using spy::gameplay::Movement;
    using spy::gameplay::State;
    using spy::gadget::Gadget;

    Scenario decodedScenario;
    decodedScenario = input.get<Scenario>();

    FieldMap field(decodedScenario);

    Gadget g1(spy::gadget::GadgetEnum::BOWLER_BLADE);
    Gadget g2(spy::gadget::GadgetEnum::CHICKEN_FEED);
    Gadget g3(spy::gadget::GadgetEnum::FOG_TIN);
    Gadget g4(spy::gadget::GadgetEnum::GAS_GLOSS);
    Gadget g5(spy::gadget::GadgetEnum::DIAMOND_COLLAR);

    field.getField({2, 2}).setGadget(g1);
    field.getField({3, 2}).setGadget(g2);
    field.getField({4, 3}).setGadget(g3);
    field.getField({4, 4}).setGadget(g4);
    field.getField({5, 3}).setGadget(g5);

    UUID uuid1 = UUID::generate();

    Character c1(uuid1, "dummy");

    c1.setCoordinates({1, 2});

    CharacterSet characters = {c1};

    Movement move1(false, {2, 2}, uuid1, {1, 2});
    Movement move2(false, {3, 2}, uuid1, {2, 2});
    Movement move3(false, {4, 3}, uuid1, {3, 2});
    Movement move4(false, {4, 4}, uuid1, {4, 3});
    Movement move5(false, {5, 3}, uuid1, {4, 4});
    Movement move6(false, {6, 3}, uuid1, {5, 3});

    State state(0, field, {}, characters, std::nullopt, std::nullopt);

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

