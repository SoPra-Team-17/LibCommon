//
// Created by jonas on 12.04.20.
//

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <network/messages/MetaInformation.hpp>

TEST(messages, MetaInformation) {
    auto parsedInput = R"({
  "creationDate": "",
  "playerId": "00000000-0000-0000-0000-000000000000",
  "type": "META_INFORMATION",
  "information": {
    "Spectator.Count": 2,
    "Spectator.Members": [
      "P1",
      "P2"
    ]
  }
})"_json;

    spy::network::messages::MetaInformation metaInformation;

    EXPECT_NO_THROW(metaInformation = parsedInput.get<spy::network::messages::MetaInformation>());
    EXPECT_EQ(std::get<int>(metaInformation.getInformation().at("Spectator.Count")), 2);
    std::vector<std::string> spectators{"P1", "P2"};
    EXPECT_EQ(std::get<std::vector<std::string>>(metaInformation.getInformation().at("Spectator.Members")), spectators);
}