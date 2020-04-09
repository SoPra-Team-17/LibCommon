//
// Created by marco on 09.04.20.
//

#include <gtest/gtest.h>
#include <network/messages/HelloMessage.hpp>
#include <network/RoleEnum.hpp>
#include <util/UUID.hpp>
#include <iostream>

TEST(messages, helloMessage){
    using namespace spy::network;
    using namespace spy::network::messages;
    std::string str = "name123";
    RoleEnum role = RoleEnum::PLAYER;
    HelloMessage m(spy::util::UUID(), str, role);

    EXPECT_EQ(m.getRole(), role);
    EXPECT_EQ(m.getName(), str);

    nlohmann::json json = m;
    std::string serialized = json.dump();
    std::string expected = R"({"creationDate":"","name":"name123","playerId":"00000000-0000-0000-0000-000000000000","role":"PLAYER","type":"HELLO"})";
    EXPECT_EQ(serialized, expected);


    auto input = R"({"creationDate":"","name":"name123","playerId":"00000000-0000-0000-0000-000000000000","role":"PLAYER","type":"HELLO"})"_json;
    auto decodedMessage = input.get<HelloMessage>();

    EXPECT_EQ(decodedMessage.getName(), m.getName());
}

