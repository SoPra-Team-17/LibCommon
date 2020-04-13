//
// Created by jonas on 13.04.20.
//


#include <gtest/gtest.h>
#include <network/messages/Hello.hpp>


TEST(messages, debugInfo) {
    std::string debug = "DEBUG MESSAGE TEST";
    spy::network::messages::Hello helloMessage{{}, "Name", spy::network::RoleEnum::AI};
    helloMessage.setDebugMessage(debug);
    nlohmann::json j = helloMessage;
    std::string encodedMessage = j.dump();

    nlohmann::json parsedMessage = nlohmann::json::parse(encodedMessage);
    auto m = parsedMessage.get<spy::network::MessageContainer>();
    ASSERT_TRUE(m.getDebugMessage().has_value());
    EXPECT_EQ(m.getDebugMessage().value(), debug);
}
