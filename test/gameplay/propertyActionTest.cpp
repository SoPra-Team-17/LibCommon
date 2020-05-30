//
// Created by jonas on 10.04.20.
//

#include <gtest/gtest.h>
#include <datatypes/gameplay/PropertyAction.hpp>
#include <util/OperationSerialization.hpp>


TEST(PropertyAction, encode) {
    spy::gameplay::PropertyAction propertyAction(true, {1, 2}, spy::util::UUID("12345678-1234-1234-1234-1234567890AB"),
                                                 spy::character::PropertyEnum::BANG_AND_BURN);
    nlohmann::json j;
    EXPECT_NO_THROW(j = propertyAction);
    EXPECT_EQ(j.dump(),
              R"({"characterId":"12345678-1234-1234-1234-1234567890ab","isEnemy":null,"successful":true,"target":{"x":1,"y":2},"type":"PROPERTY_ACTION","usedProperty":"BANG_AND_BURN"})");
}

TEST(PropertyAction, decode) {
    spy::gameplay::PropertyAction expected(true, {1, 2}, spy::util::UUID("12345678-1234-1234-1234-1234567890AB"),
                                           spy::character::PropertyEnum::BANG_AND_BURN);
    std::string input = R"({"characterId":"12345678-1234-1234-1234-1234567890ab","isEnemy":null,"successful":true,"target":{"x":1,"y":2},"type":"PROPERTY_ACTION","usedProperty":"BANG_AND_BURN"})";

    auto j = nlohmann::json::parse(input);
    auto operation = j.get<std::shared_ptr<spy::gameplay::BaseOperation>>();
    EXPECT_EQ(operation->getType(), spy::gameplay::OperationEnum::PROPERTY_ACTION);
    spy::gameplay::PropertyAction decodedAction{};
    EXPECT_NO_THROW(decodedAction = j.get<spy::gameplay::PropertyAction>());
    EXPECT_EQ(decodedAction, expected);
}