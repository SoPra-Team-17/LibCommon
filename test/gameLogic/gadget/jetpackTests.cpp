/**
 * @file   jetpackTests.cpp
 * @author Dominik Authaler
 * @date   30.04.2020 (creation)
 * @brief  Unit tests for the validation and execution of jetpack gadget actions.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "gameLogic/validation/ActionValidator.hpp"

TEST_F(GadgetActionTests, Jetpack_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;
    using spy::gadget::Gadget;

    auto jetpack = std::make_shared<Gadget>(GadgetEnum::JETPACK);

    state.getCharacters().getByUUID(uuid1)->setCoordinates(Point{4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates(Point{5, 3});
    state.getCharacters().getByUUID(uuid3)->setCoordinates(Point{4, 2});
    state.getCharacters().getByUUID(uuid5)->setCoordinates(Point{6, 6});

    state.getCharacters().getByUUID(uuid1)->addGadget(jetpack);
    state.getCharacters().getByUUID(uuid5)->addGadget(jetpack);

    auto g1  = std::make_shared<GadgetAction>(GadgetAction(false, {5, 3}, uuid2, GadgetEnum::JETPACK));
    auto g2  = std::make_shared<GadgetAction>(GadgetAction(false, {4, 3}, uuid1, GadgetEnum::JETPACK));
    auto g3  = std::make_shared<GadgetAction>(GadgetAction(false, {4, 4}, uuid1, GadgetEnum::JETPACK));
    auto g4  = std::make_shared<GadgetAction>(GadgetAction(false, {4, 2}, uuid1, GadgetEnum::JETPACK));
    auto g5  = std::make_shared<GadgetAction>(GadgetAction(false, {6, 7}, uuid5, GadgetEnum::JETPACK));
    auto g6  = std::make_shared<GadgetAction>(GadgetAction(false, {4, 1}, uuid1, GadgetEnum::JETPACK));
    auto g7  = std::make_shared<GadgetAction>(GadgetAction(false, {0, 0}, uuid1, GadgetEnum::JETPACK));
    auto g8  = std::make_shared<GadgetAction>(GadgetAction(false, {1, 1}, uuid1, GadgetEnum::JETPACK));
    auto g9  = std::make_shared<GadgetAction>(GadgetAction(false, {3, 1}, uuid1, GadgetEnum::JETPACK));
    auto g10 = std::make_shared<GadgetAction>(GadgetAction(false, {3, 3}, uuid1, GadgetEnum::JETPACK));
    auto g11 = std::make_shared<GadgetAction>(GadgetAction(false, {5, 5}, uuid1, GadgetEnum::JETPACK));
    auto g12 = std::make_shared<GadgetAction>(GadgetAction(false, {0, 4}, uuid1, GadgetEnum::JETPACK));

    EXPECT_FALSE(ActionValidator::validate(state, g1, config)) << "character has no jetpack --> invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g2, config)) << "no move --> useless, but valid";
    EXPECT_TRUE(ActionValidator::validate(state, g3, config)) << "target: free field --> valid";
    EXPECT_FALSE(ActionValidator::validate(state, g4, config)) << "target: character --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g5, config)) << "target outside map --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g6, config)) << "target: character --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g7, config)) << "target: wall --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g8, config)) << "target: fireplace --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g9, config)) << "target: bar table --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g10, config)) << "target: roulette table --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g11, config)) << "target: safe --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g12, config)) << "target: bar seat --> invalid";
}