/**
 * @file   diamondCollarTests.cpp
 * @author Dominik Authaler
 * @date   01.05.2020 (creation)
 * @brief  Unit tests for the validation and execution of gadget actions with the diamond collar.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "datatypes/validation/ActionValidator.hpp"

TEST_F(GadgetActionTests, DiamondCollar_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;

    spy::gadget::Gadget collar{spy::gadget::GadgetEnum::DIAMOND_COLLAR};

    state.getCharacters().getByUUID(uuid1)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({5, 3});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({5, 2});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({6, 6});

    state.setCatCoordinates(Point{4, 4});

    state.getCharacters().getByUUID(uuid1)->addGadget(collar);
    state.getCharacters().getByUUID(uuid3)->addGadget(collar);
    state.getCharacters().getByUUID(uuid5)->addGadget(collar);

    GadgetAction g1(false, {4, 4}, uuid2, GadgetEnum::DIAMOND_COLLAR);
    GadgetAction g2(false, {4, 3}, uuid1, GadgetEnum::DIAMOND_COLLAR);
    GadgetAction g3(false, {4, 2}, uuid1, GadgetEnum::DIAMOND_COLLAR);
    GadgetAction g4(false, {4, 4}, uuid1, GadgetEnum::DIAMOND_COLLAR);
    GadgetAction g5(false, {6, 7}, uuid5, GadgetEnum::DIAMOND_COLLAR);
    GadgetAction g6(false, {4, 4}, uuid3, GadgetEnum::DIAMOND_COLLAR);

    EXPECT_FALSE(ActionValidator::validate(state, g1)) << "character has no diamond collar --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g2)) << "give oneself --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g3)) << "aim on field without cat --> invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g4))  << "aim on cat --> valid";
    EXPECT_FALSE(ActionValidator::validate(state, g5)) << "target outside map --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g6)) << "target outside range --> invalid";
}
