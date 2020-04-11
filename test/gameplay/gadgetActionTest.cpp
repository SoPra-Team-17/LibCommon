//
// Created by jonas on 10.04.20.
//

#include <gtest/gtest.h>
#include <datatypes/gameplay/GadgetAction.hpp>

TEST(GadgetAction, encode) {
    spy::gameplay::GadgetAction ga(true, {1, 2}, spy::util::UUID("12345678-1234-1234-1234-1234567890AB"),
                                   spy::gadget::GadgetEnum::JETPACK);
    nlohmann::json j;
    EXPECT_NO_THROW(j = ga);
    EXPECT_EQ(j.dump(),
              R"({"characterId":"12345678-1234-1234-1234-1234567890ab","gadget":"JETPACK","successful":true,"target":{"x":1,"y":2},"type":"GADGET_ACTION"})");
}

TEST(GadgetAction, decode) {
    spy::gameplay::GadgetAction expected(true, {1, 2}, spy::util::UUID("12345678-1234-1234-1234-1234567890AB"),
                                         spy::gadget::GadgetEnum::JETPACK);
    std::string input = R"({"characterId":"12345678-1234-1234-1234-1234567890ab","gadget":"JETPACK","successful":true,"target":{"x":1,"y":2},"type":"GADGET_ACTION"})";

    auto j = nlohmann::json::parse(input);
    auto operation = j.get<spy::gameplay::Operation>();
    EXPECT_EQ(operation.getType(), spy::gameplay::OperationEnum::GADGET_ACTION);
    spy::gameplay::GadgetAction decodedAction{};
    EXPECT_NO_THROW(decodedAction = j.get<spy::gameplay::GadgetAction>());
    EXPECT_EQ(decodedAction, expected);
}