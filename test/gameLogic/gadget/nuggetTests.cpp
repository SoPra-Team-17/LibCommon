/**
 * @file   nuggetTests.cpp
 * @author Dominik Authaler
 * @date   30.04.2020 (creation)
 * @brief  Unit tests for the validation and execution of nugget gadget actions.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "datatypes/validation/ActionValidator.hpp"

TEST_F(GadgetActionTests, Nugget_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;

    spy::gadget::Gadget nugget{spy::gadget::GadgetEnum::NUGGET};

    state.getCharacters().getByUUID(uuid1)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({5, 3});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({4, 2});
    state.getCharacters().getByUUID(uuid4)->setCoordinates({4, 5});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({6, 6});

    state.getCharacters().getByUUID(uuid1)->addGadget(nugget);
    state.getCharacters().getByUUID(uuid5)->addGadget(nugget);

    GadgetAction g1(false, {5, 3}, uuid2, GadgetEnum::NUGGET);
    GadgetAction g2(false, {4, 3}, uuid1, GadgetEnum::NUGGET);
    GadgetAction g3(false, {4, 4}, uuid1, GadgetEnum::NUGGET);
    GadgetAction g4(false, {4, 2}, uuid1, GadgetEnum::NUGGET);
    GadgetAction g5(false, {6, 7}, uuid5, GadgetEnum::NUGGET);
    GadgetAction g6(false, {4, 5}, uuid1, GadgetEnum::NUGGET);

    EXPECT_FALSE(ActionValidator::validate(state, g1));     // character has no nugget --> invalid
    EXPECT_FALSE(ActionValidator::validate(state, g2));     // give oneself --> invalid
    EXPECT_FALSE(ActionValidator::validate(state, g3));     // aim on field without a character --> invalid
    EXPECT_TRUE(ActionValidator::validate(state, g4));      // aim on character --> valid
    EXPECT_FALSE(ActionValidator::validate(state, g5));     // target outside map --> invalid
    EXPECT_FALSE(ActionValidator::validate(state, g6));     // target outside range --> invalid
}