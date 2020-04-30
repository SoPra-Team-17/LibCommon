/**
 * @file   poisonPillTests.cpp
 * @author Dominik Authaler
 * @date   29.04.2020 (creation)
 * @brief  Unit tests for the validation and execution of poison pills gadget actions.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "datatypes/validation/ActionValidator.hpp"

TEST_F(GadgetActionTests, PoisonPills_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;

    spy::gadget::Gadget poisonPills{spy::gadget::GadgetEnum::POISON_PILLS};
    spy::gadget::Gadget cocktail{spy::gadget::GadgetEnum::COCKTAIL};

    state.getCharacters().getByUUID(uuid1)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({5, 3});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({4, 2});
    state.getCharacters().getByUUID(uuid4)->setCoordinates({4, 5});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({6, 6});
    state.getCharacters().getByUUID(uuid6)->setCoordinates({1, 2});
    state.getCharacters().getByUUID(uuid7)->setCoordinates({4, 1});

    state.getCharacters().getByUUID(uuid1)->addGadget(poisonPills);
    state.getCharacters().getByUUID(uuid1)->addGadget(cocktail);
    state.getCharacters().getByUUID(uuid2)->addGadget(cocktail);
    state.getCharacters().getByUUID(uuid4)->addGadget(cocktail);
    state.getCharacters().getByUUID(uuid5)->addGadget(poisonPills);
    state.getCharacters().getByUUID(uuid6)->addGadget(poisonPills);

    state.getMap().getField(1, 3).setGadget(cocktail);

    GadgetAction g1(false, {5, 3}, uuid2, GadgetEnum::POISON_PILLS);
    GadgetAction g2(false, {4, 3}, uuid1, GadgetEnum::POISON_PILLS);
    GadgetAction g3(false, {4, 4}, uuid1, GadgetEnum::POISON_PILLS);
    GadgetAction g4(false, {4, 2}, uuid1, GadgetEnum::POISON_PILLS);
    GadgetAction g5(false, {6, 7}, uuid5, GadgetEnum::POISON_PILLS);
    GadgetAction g6(false, {4, 5}, uuid1, GadgetEnum::POISON_PILLS);
    GadgetAction g7(false, {6, 6}, uuid5, GadgetEnum::POISON_PILLS);
    GadgetAction g8(false, {5, 3}, uuid1, GadgetEnum::POISON_PILLS);
    GadgetAction g9(false, {1, 3}, uuid6, GadgetEnum::POISON_PILLS);
    GadgetAction g10(false, {3, 1}, uuid7, GadgetEnum::POISON_PILLS);

    EXPECT_FALSE(ActionValidator::validate(state, g1)) << "character has no pills --> invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g2)) << "aim on own cocktail --> valid";
    EXPECT_FALSE(ActionValidator::validate(state, g3)) << "aim on empty field --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g4)) << "aim on character without cocktail --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g5)) << "target outside map --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g6)) << "target out of range --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g7)) << "aim on oneself without a cocktail --> invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g8)) << "aim on character with cocktail --> valid";
    EXPECT_TRUE(ActionValidator::validate(state, g9)) << "aim on cocktail on a bar table --> valid";
    EXPECT_FALSE(ActionValidator::validate(state, g10)) << "aim on empty bar table --> invalid";
}
