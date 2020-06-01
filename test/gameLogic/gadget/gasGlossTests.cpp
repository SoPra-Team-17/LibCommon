/**
 * @file   gasGlossTests.cpp
 * @author Dominik Authaler
 * @date   30.04.2020 (creation)
 * @brief  Unit tests for the validation and execution of gas gloss gadget actions.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "gameLogic/validation/ActionValidator.hpp"

TEST_F(GadgetActionTests, GasGloss_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;
    using spy::gadget::Gadget;

    auto gloss = std::make_shared<Gadget>(GadgetEnum::GAS_GLOSS);

    state.getCharacters().getByUUID(uuid1)->setCoordinates(Point{4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates(Point{5, 3});
    state.getCharacters().getByUUID(uuid3)->setCoordinates(Point{4, 2});
    state.getCharacters().getByUUID(uuid4)->setCoordinates(Point{4, 5});
    state.getCharacters().getByUUID(uuid5)->setCoordinates(Point{6, 6});

    state.getCharacters().getByUUID(uuid1)->addGadget(gloss);
    state.getCharacters().getByUUID(uuid5)->addGadget(gloss);

    auto g1 = std::make_shared<GadgetAction>(GadgetAction(false, {5, 3}, uuid2, GadgetEnum::GAS_GLOSS));
    auto g2 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 3}, uuid1, GadgetEnum::GAS_GLOSS));
    auto g3 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 4}, uuid1, GadgetEnum::GAS_GLOSS));
    auto g4 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 2}, uuid1, GadgetEnum::GAS_GLOSS));
    auto g5 = std::make_shared<GadgetAction>(GadgetAction(false, {6, 7}, uuid5, GadgetEnum::GAS_GLOSS));
    auto g6 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 5}, uuid1, GadgetEnum::GAS_GLOSS));

    EXPECT_FALSE(ActionValidator::validate(state, g1, config)) << "character has no gas gloss --> invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g2, config)) << "hurt oneself --> stupid, but valid";
    EXPECT_FALSE(ActionValidator::validate(state, g3, config)) << "aim on field without a character --> invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g4, config)) << "aim on character --> valid";
    EXPECT_FALSE(ActionValidator::validate(state, g5, config)) << "target outside map --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g6, config)) << "target outside range --> invalid";
}