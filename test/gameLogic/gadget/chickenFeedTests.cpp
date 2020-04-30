/**
 * @file   chickenFeedTests.cpp
 * @author Dominik Authaler
 * @date   29.04.2020 (creation)
 * @brief  Unit tests for the validation and execution of chicken feed gadget actions.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "datatypes/validation/ActionValidator.hpp"

TEST_F(GadgetActionTests, ChickenFeed_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;

    spy::gadget::Gadget chickenFeed{spy::gadget::GadgetEnum::CHICKEN_FEED};

    state.getCharacters().getByUUID(uuid1)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({5, 3});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({4, 2});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({6, 6});

    state.getCharacters().getByUUID(uuid1)->addGadget(chickenFeed);
    state.getCharacters().getByUUID(uuid5)->addGadget(chickenFeed);

    GadgetAction g1(false, {5, 3}, uuid2, GadgetEnum::CHICKEN_FEED);
    GadgetAction g2(false, {4, 3}, uuid1, GadgetEnum::CHICKEN_FEED);
    GadgetAction g3(false, {4, 4}, uuid1, GadgetEnum::CHICKEN_FEED);
    GadgetAction g4(false, {4, 2}, uuid1, GadgetEnum::CHICKEN_FEED);
    GadgetAction g5(false, {6, 7}, uuid5, GadgetEnum::CHICKEN_FEED);

    EXPECT_FALSE(ActionValidator::validate(state, g1));     // character doesn't posses gadget --> invalid
    EXPECT_FALSE(ActionValidator::validate(state, g2));     // apply to oneself --> invalid
    EXPECT_FALSE(ActionValidator::validate(state, g3));     // apply to empty field --> invalid
    EXPECT_TRUE(ActionValidator::validate(state, g4));      // apply to character --> valid
    EXPECT_FALSE(ActionValidator::validate(state, g5));     // target outside map --> invalid
}



