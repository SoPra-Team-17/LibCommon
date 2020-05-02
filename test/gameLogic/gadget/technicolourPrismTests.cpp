/**
 * @file   technicolourPrismTests.cpp
 * @author Dominik Authaler
 * @date   29.04.2020 (creation)
 * @brief  Unit tests for the validation and execution of technicolour prism gadget actions.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "gameLogic/validation/ActionValidator.hpp"

TEST_F(GadgetActionTests, TechnicolourPrism_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;

    spy::gadget::Gadget prism{spy::gadget::GadgetEnum::TECHNICOLOUR_PRISM};

    state.getCharacters().getByUUID(uuid1)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({5, 3});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({3, 2});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({6, 6});

    state.getCharacters().getByUUID(uuid1)->addGadget(prism);
    state.getCharacters().getByUUID(uuid5)->addGadget(prism);

    auto g1 = std::make_shared<GadgetAction>(GadgetAction(false, {3, 3}, uuid1, GadgetEnum::TECHNICOLOUR_PRISM));
    auto g2 = std::make_shared<GadgetAction>(GadgetAction(false, {3, 3}, uuid2, GadgetEnum::TECHNICOLOUR_PRISM));
    auto g3 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 2}, uuid1, GadgetEnum::TECHNICOLOUR_PRISM));
    auto g4 = std::make_shared<GadgetAction>(GadgetAction(false, {3, 3}, uuid3, GadgetEnum::TECHNICOLOUR_PRISM));
    auto g5 = std::make_shared<GadgetAction>(GadgetAction(false, {6, 7}, uuid5, GadgetEnum::TECHNICOLOUR_PRISM));

    EXPECT_TRUE(ActionValidator::validate(state, g1, config)) << "roulette table is target in range --> valid";
    EXPECT_FALSE(ActionValidator::validate(state, g2, config)) << "roulette table out of range --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g3, config)) << "target is no roulette table --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g4, config)) << "character has no prism --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g5, config)) << "target field is outside --> invalid";
}



