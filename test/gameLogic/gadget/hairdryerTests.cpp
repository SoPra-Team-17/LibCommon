/**
 * @file   hairdryerTests.cpp
 * @author Dominik Authaler
 * @date   29.04.2020 (creation)
 * @brief  Unit tests for the validation and execution of hairdryer gadget actions.
 */

#include <gtest/gtest.h>
#include "gadgetActionFixture.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "gameLogic/execution/ActionExecutor.hpp"

TEST_F(GadgetActionTests, Hairdryer_Validate) {
    using spy::gameplay::ActionValidator;
    using spy::gadget::GadgetEnum;
    using spy::character::PropertyEnum;
    using spy::util::Point;
    using spy::gameplay::GadgetAction;

    spy::gadget::Gadget hairdryer{spy::gadget::GadgetEnum::HAIRDRYER};

    state.getCharacters().getByUUID(uuid1)->setCoordinates({4, 3});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({4, 2});
    state.getCharacters().getByUUID(uuid3)->setCoordinates({4, 4});
    state.getCharacters().getByUUID(uuid4)->setCoordinates({5, 3});
    state.getCharacters().getByUUID(uuid5)->setCoordinates({6, 6});

    state.getCharacters().getByUUID(uuid1)->addGadget(hairdryer);
    state.getCharacters().getByUUID(uuid5)->addGadget(hairdryer);

    auto g1 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 3}, uuid2, GadgetEnum::HAIRDRYER));
    auto g2 = std::make_shared<GadgetAction>(GadgetAction(false, {6, 7}, uuid5, GadgetEnum::HAIRDRYER));
    auto g3 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 3}, uuid1, GadgetEnum::HAIRDRYER));
    auto g4 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 3}, uuid1, GadgetEnum::HAIRDRYER));
    auto g5 = std::make_shared<GadgetAction>(GadgetAction(false, {2, 3}, uuid1, GadgetEnum::HAIRDRYER));
    auto g6 = std::make_shared<GadgetAction>(GadgetAction(false, {3, 3}, uuid1, GadgetEnum::HAIRDRYER));
    auto g7 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 2}, uuid1, GadgetEnum::HAIRDRYER));
    auto g8 = std::make_shared<GadgetAction>(GadgetAction(false, {4, 4}, uuid1, GadgetEnum::HAIRDRYER));

    EXPECT_FALSE(ActionValidator::validate(state, g1, config)) << "execution without owning a hairdryer is invalid";
    EXPECT_FALSE(ActionValidator::validate(state, g2, config)) << "execution on a field outside is invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g3, config)) << "execution on oneself without CLAMMY_CLOTHES is valid";

    std::set<PropertyEnum> properties = {PropertyEnum::CLAMMY_CLOTHES};
    state.getCharacters().getByUUID(uuid5)->setProperties(properties);
    state.getCharacters().getByUUID(uuid3)->setProperties(properties);

    EXPECT_TRUE(ActionValidator::validate(state, g4, config)) << "execution on oneself with CLAMMY_CLOTHES is valid";
    EXPECT_FALSE(ActionValidator::validate(state, g5, config)) << "target out of range --> invalid";

    EXPECT_FALSE(ActionValidator::validate(state, g6, config)) << "execution on empty field is invalid";
    EXPECT_TRUE(ActionValidator::validate(state, g7, config)) << "execution on character without CLAMMY_CLOTHES is valid";
    EXPECT_TRUE(ActionValidator::validate(state, g8, config)) << "execution on character with CLAMMY_CLOTHES is valid";
}

TEST_F(GadgetActionTests, HairDryer_Execute) {
    using spy::character::PropertyEnum;
    using spy::gameplay::ActionExecutor;
    using spy::gameplay::GadgetAction;

    state.getCharacters().getByUUID(uuid1)->setCoordinates({1, 2});
    state.getCharacters().getByUUID(uuid2)->setCoordinates({2, 2});

    auto c1 = state.getCharacters().getByUUID(uuid1);
    auto c2 = state.getCharacters().getByUUID(uuid2);

    c2->setProperties({PropertyEnum::CLAMMY_CLOTHES});
    ASSERT_TRUE(c2->getProperties().find(PropertyEnum::CLAMMY_CLOTHES) != c2->getProperties().end());

    auto a = std::make_shared<GadgetAction>(GadgetAction{false, c2->getCoordinates().value(), uuid1, spy::gadget::GadgetEnum::HAIRDRYER});
    ActionExecutor::execute(state, a, config);

    EXPECT_TRUE(c2->getProperties().find(PropertyEnum::CLAMMY_CLOTHES) == c2->getProperties().end())
                        << "Expect CLAMMY_CLOTHES to be removed from character 2";
}



