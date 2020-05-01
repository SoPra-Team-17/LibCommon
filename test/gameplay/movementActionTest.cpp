//
// Created by jonas on 10.04.20.
//

#include <gtest/gtest.h>
#include <datatypes/gameplay/Movement.hpp>
#include <util/OperationSerialization.hpp>


TEST(Movement, encode) {
    spy::gameplay::Movement movement(true, {1, 2}, spy::util::UUID("12345678-1234-1234-1234-1234567890AB"), {3, 4});
    nlohmann::json j;
    EXPECT_NO_THROW(j = movement);
    EXPECT_EQ(j.dump(),
              R"({"characterId":"12345678-1234-1234-1234-1234567890ab","from":{"x":3,"y":4},"successful":true,"target":{"x":1,"y":2},"type":"MOVEMENT"})");
}

TEST(Movement, decode) {
    spy::gameplay::Movement expected(true, {1, 2}, spy::util::UUID("12345678-1234-1234-1234-1234567890AB"), {3, 4});
    std::string input = R"({"characterId":"12345678-1234-1234-1234-1234567890ab","from":{"x":3,"y":4},"successful":true,"target":{"x":1,"y":2},"type":"MOVEMENT"})";

    auto j = nlohmann::json::parse(input);
    auto operation = j.get<std::shared_ptr<spy::gameplay::BaseOperation>>();
    EXPECT_EQ(operation->getType(), spy::gameplay::OperationEnum::MOVEMENT);
    spy::gameplay::Movement decodedAction{};
    EXPECT_NO_THROW(decodedAction = j.get<spy::gameplay::Movement>());
    EXPECT_EQ(decodedAction, expected);
}