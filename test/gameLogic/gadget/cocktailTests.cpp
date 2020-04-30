/**
 * @file   cocktailTests.cpp
 * @author Dominik Authaler
 * @date   29.04.2020 (creation)
 * @brief  Unit tests for the validation and execution of cocktail gadget actions.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "datatypes/validation/ActionValidator.hpp"

TEST_F(GadgetActionTests, Cocktail_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;

    spy::gadget::Gadget cocktail{spy::gadget::GadgetEnum::COCKTAIL};

    state.getCharacters().getByUUID(uuid1)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({5, 3});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({4, 2});
    state.getCharacters().getByUUID(uuid4)->setCoordinates({4, 5});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({6, 6});

    state.getCharacters().getByUUID(uuid1)->addGadget(cocktail);
    state.getCharacters().getByUUID(uuid5)->addGadget(cocktail);

    GadgetAction g1(false, {5, 3}, uuid2, GadgetEnum::COCKTAIL);
    GadgetAction g2(false, {4, 3}, uuid1, GadgetEnum::COCKTAIL);
    GadgetAction g3(false, {4, 4}, uuid1, GadgetEnum::COCKTAIL);
    GadgetAction g4(false, {4, 2}, uuid1, GadgetEnum::COCKTAIL);
    GadgetAction g5(false, {6, 7}, uuid5, GadgetEnum::COCKTAIL);
    GadgetAction g6(false, {4, 5}, uuid1, GadgetEnum::COCKTAIL);

    EXPECT_FALSE(ActionValidator::validate(state, g1));     // character has no cocktail --> invalid
    EXPECT_TRUE(ActionValidator::validate(state, g2));      // drink cocktail --> valid
    EXPECT_FALSE(ActionValidator::validate(state, g3));     // spill on empty field --> invalid
    EXPECT_TRUE(ActionValidator::validate(state, g4));      // spill on character --> valid
    EXPECT_FALSE(ActionValidator::validate(state, g5));     // target outside map --> invalid
    EXPECT_FALSE(ActionValidator::validate(state, g6));     // target out of range --> invalid
}



