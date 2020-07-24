//
// Created by marco on 09.04.20.
//

#include <gtest/gtest.h>
#include <network/messages/Hello.hpp>
#include <network/RoleEnum.hpp>
#include <util/UUID.hpp>
#include <iostream>

TEST(messages, helloMessage) {
    using namespace spy::network;
    using namespace spy::network::messages;
    std::string str = "name123";
    RoleEnum role = RoleEnum::PLAYER;
    Hello m(spy::util::UUID{"6a1333d0-2317-4044-9d37-047d29205011"}, str, role);

    EXPECT_EQ(m.getRole(), role);
    EXPECT_EQ(m.getName(), str);

    nlohmann::json json = m;
    std::string serialized = json.dump();
    std::string expected =
            R"({"clientId":"6a1333d0-2317-4044-9d37-047d29205011","creationDate":")" + m.getCreationDate() +
            R"(","name":"name123","role":"PLAYER","type":"HELLO"})";
    EXPECT_EQ(serialized, expected);


    auto input = R"({"creationDate":"","name":"name123","clientId":"00000000-0000-0000-0000-000000000000","role":"PLAYER","type":"HELLO"})"_json;
    auto decodedMessage = input.get<Hello>();

    EXPECT_EQ(decodedMessage.getName(), m.getName());
}

TEST(messages, helloMessageWithoutClientId) {
    std::string messageString = R"({"name":"Admiral Edward Davidov","role":"SPECTATOR","type":"HELLO","creationDate":"Jul 22, 2020, 7:45:42 PM"})";
    auto decodedJson = nlohmann::json::parse(messageString);
    auto message = decodedJson.get<spy::network::messages::Hello>();
    EXPECT_EQ(message.getName(), "Admiral Edward Davidov");
    EXPECT_EQ(message.getRole(), spy::network::RoleEnum::SPECTATOR);
    EXPECT_EQ(message.getCreationDate(), "Jul 22, 2020, 7:45:42 PM");
}
