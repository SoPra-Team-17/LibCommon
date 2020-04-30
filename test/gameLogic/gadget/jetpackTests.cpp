/**
 * @file   jetpackTests.cpp
 * @author Dominik Authaler
 * @date   30.04.2020 (creation)
 * @brief  Unit tests for the validation and execution of jetpack gadget actions.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "datatypes/validation/ActionValidator.hpp"

TEST_F(GadgetActionTests, Jetpack_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;

    spy::gadget::Gadget jetpack{spy::gadget::GadgetEnum::JETPACK};

    state.getCharacters().getByUUID(uuid1)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({5, 3});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({4, 2});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({6, 6});

    state.getCharacters().getByUUID(uuid1)->addGadget(jetpack);
    state.getCharacters().getByUUID(uuid5)->addGadget(jetpack);

    GadgetAction g1(false, {5, 3}, uuid2, GadgetEnum::JETPACK);
    GadgetAction g2(false, {4, 3}, uuid1, GadgetEnum::JETPACK);
    GadgetAction g3(false, {4, 4}, uuid1, GadgetEnum::JETPACK);
    GadgetAction g4(false, {4, 2}, uuid1, GadgetEnum::JETPACK);
    GadgetAction g5(false, {6, 7}, uuid5, GadgetEnum::JETPACK);
    GadgetAction g6(false, {4, 1}, uuid1, GadgetEnum::JETPACK);
    GadgetAction g7(false, {0, 0}, uuid1, GadgetEnum::JETPACK);
    GadgetAction g8(false, {1, 1}, uuid1, GadgetEnum::JETPACK);
    GadgetAction g9(false, {3, 1}, uuid1, GadgetEnum::JETPACK);
    GadgetAction g10(false, {3, 3}, uuid1, GadgetEnum::JETPACK);
    GadgetAction g11(false, {5, 5}, uuid1, GadgetEnum::JETPACK);
    GadgetAction g12(false, {0, 4}, uuid1, GadgetEnum::JETPACK);

    EXPECT_FALSE(ActionValidator::validate(state, g1)) << "character has no jetpack --> invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g2)) << "no move --> useless, but valid";
    EXPECT_TRUE(ActionValidator::validate(state, g3)) << "target: free field --> valid";
    EXPECT_FALSE(ActionValidator::validate(state, g4)) << "target: character --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g5)) << "target outside map --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g6)) << "target: character --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g7)) << "target: wall --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g8)) << "target: fireplace --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g9)) << "target: bar table --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g10)) << "target: roulette table --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g11)) << "target: safe --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g12)) << "target: bar seat --> invalid";
}