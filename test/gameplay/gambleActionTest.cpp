//
// Created by jonas on 10.04.20.
//

#include <gtest/gtest.h>
#include <datatypes/gameplay/GambleAction.hpp>
#include <datatypes/gameplay/OperationJson.hpp>


TEST(GambleAction, encode) {
    spy::gameplay::GambleAction ga(true, {1, 2}, spy::util::UUID("12345678-1234-1234-1234-1234567890AB"), 3);
    nlohmann::json j;
    EXPECT_NO_THROW(j = ga);
    EXPECT_EQ(j.dump(),
              R"({"characterId":"12345678-1234-1234-1234-1234567890ab","stake":3,"successful":true,"target":{"x":1,"y":2},"type":"GAMBLE_ACTION"})");
}

TEST(GambleAction, decode) {
    spy::gameplay::GambleAction expected(true, {1, 2}, spy::util::UUID("12345678-1234-1234-1234-1234567890AB"),
                                         3);
    std::string input = R"({"characterId":"12345678-1234-1234-1234-1234567890ab","stake":3,"successful":true,"target":{"x":1,"y":2},"type":"GAMBLE_ACTION"})";

    auto j = nlohmann::json::parse(input);
    auto operation = spy::gameplay::OperationJson::fromJson(j);
    EXPECT_EQ(operation->getType(), spy::gameplay::OperationEnum::GAMBLE_ACTION);
    spy::gameplay::GambleAction decodedAction{};
    EXPECT_NO_THROW(decodedAction = j.get<spy::gameplay::GambleAction>());
    EXPECT_EQ(decodedAction, expected);
}