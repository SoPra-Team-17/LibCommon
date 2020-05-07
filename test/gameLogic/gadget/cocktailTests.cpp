/**
 * @file   cocktailTests.cpp
 * @author Dominik Authaler
 * @date   29.04.2020 (creation)
 * @brief  Unit tests for the validation and execution of cocktail gadget actions.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "datatypes/gadgets/Cocktail.hpp"

TEST_F(GadgetActionTests, Cocktail_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;
    using spy::gadget::Gadget;

    auto cocktail = std::make_shared<spy::gadget::Cocktail>();

    state.getCharacters().getByUUID(uuid1)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({5, 3});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({4, 2});
    state.getCharacters().getByUUID(uuid4)->setCoordinates({4, 5});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({6, 6});

    state.getCharacters().getByUUID(uuid1)->addGadget(cocktail);
    state.getCharacters().getByUUID(uuid5)->addGadget(cocktail);

    auto g1 = std::make_shared<GadgetAction>(GadgetAction(false, {5, 3}, uuid2, GadgetEnum::COCKTAIL));
    auto g2 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 3}, uuid1, GadgetEnum::COCKTAIL));
    auto g3 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 4}, uuid1, GadgetEnum::COCKTAIL));
    auto g4 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 2}, uuid1, GadgetEnum::COCKTAIL));
    auto g5 = std::make_shared<GadgetAction>(GadgetAction(false, {6, 7}, uuid5, GadgetEnum::COCKTAIL));
    auto g6 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 5}, uuid1, GadgetEnum::COCKTAIL));
    auto g7 = std::make_shared<GadgetAction>(GadgetAction(false, {3, 1}, uuid3, GadgetEnum::COCKTAIL));
    auto g8 = std::make_shared<GadgetAction>(GadgetAction(false, {3, 1}, uuid2, GadgetEnum::COCKTAIL));

    EXPECT_FALSE(ActionValidator::validate(state, g1, config)) << "character has no cocktail --> invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g2, config)) << "drink cocktail --> valid";
    EXPECT_FALSE(ActionValidator::validate(state, g3, config)) << "spill on empty field --> invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g4, config)) << "spill on character --> valid";
    EXPECT_FALSE(ActionValidator::validate(state, g5, config)) << "target outside map --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g6, config)) << "target out of range --> invalid";

    state.getMap().getField(3, 1).setGadget(std::nullopt);
    ASSERT_FALSE(ActionValidator::validate(state, g7, config)) << "pickup cocktail from emtpy bar table --> invalid";
    state.getMap().getField(3, 1).setGadget(cocktail);
    ASSERT_TRUE(ActionValidator::validate(state, g7, config)) << "pickup cocktail --> valid";
    state.getCharacters().getByUUID(uuid3)->addGadget(cocktail);
    ASSERT_FALSE(ActionValidator::validate(state, g7, config)) << "pickup when holding a cocktail --> invalid";

    state.getMap().getField(2, 3).setGadget(cocktail);
    EXPECT_FALSE(ActionValidator::validate(state, g7, config)) << "bar table with cocktail out of range --> invalid";
}



