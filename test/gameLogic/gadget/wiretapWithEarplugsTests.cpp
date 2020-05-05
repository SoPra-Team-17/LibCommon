/**
 * @file   wiretapWithEarplugsTests.cpp
 * @author Dominik Authaler
 * @date   30.04.2020 (creation)
 * @brief  Unit tests for the validation and execution of wiretap with earplugs gadget actions.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "gameLogic/validation/ActionValidator.hpp"

TEST_F(GadgetActionTests, WiretapWithEarplugs_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;
    using spy::gadget::Gadget;

    auto earplugs = std::make_shared<Gadget>(spy::gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS);

    state.getCharacters().getByUUID(uuid1)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({5, 3});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({4, 2});
    state.getCharacters().getByUUID(uuid4)->setCoordinates({4, 5});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({6, 6});

    state.getCharacters().getByUUID(uuid1)->addGadget(earplugs);
    state.getCharacters().getByUUID(uuid5)->addGadget(earplugs);

    auto g1 = std::make_shared<GadgetAction>(GadgetAction(false, {5, 3}, uuid2, GadgetEnum::WIRETAP_WITH_EARPLUGS));
    auto g2 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 3}, uuid1, GadgetEnum::WIRETAP_WITH_EARPLUGS));
    auto g3 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 4}, uuid1, GadgetEnum::WIRETAP_WITH_EARPLUGS));
    auto g4 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 2}, uuid1, GadgetEnum::WIRETAP_WITH_EARPLUGS));
    auto g5 = std::make_shared<GadgetAction>(GadgetAction(false, {6, 7}, uuid5, GadgetEnum::WIRETAP_WITH_EARPLUGS));
    auto g6 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 5}, uuid1, GadgetEnum::WIRETAP_WITH_EARPLUGS));

    EXPECT_FALSE(ActionValidator::validate(state, g1, config)) << "character has no gadget --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g2, config)) << "aim on oneself --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g3, config)) << "aim on field without a character --> invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g4, config)) << "aim on character --> valid";
    EXPECT_FALSE(ActionValidator::validate(state, g5, config)) << "target outside map --> invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g6, config)) << "target outside range --> invalid";
}