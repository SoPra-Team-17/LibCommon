//
// Created by jonas on 10.04.20.
//

#include <gtest/gtest.h>
#include <datatypes/gameplay/Exfiltration.hpp>

TEST(Exfiltration, json_encode) {
    spy::gameplay::Exfiltration e(true, {1337, 420}, {}, {13, 37});
    nlohmann::json j;
    EXPECT_NO_THROW(j = e);
    EXPECT_EQ(j.dump(),
              R"({"characterId":"00000000-0000-0000-0000-000000000000","from":{"x":13,"y":37},"successful":true,"target":{"x":1337,"y":420},"type":"EXFILTRATION"})");
}

TEST(Exfiltration, json_decode) {
    std::string input = R"({"characterId":"00000000-0000-0000-0000-000000000000","from":{"x":13,"y":37},"successful":true,"target":{"x":1337,"y":420},"type":"EXFILTRATION"})";
    spy::gameplay::Exfiltration expected(true, {1337, 420}, {}, {13, 37});

    auto j = nlohmann::json::parse(input);
    spy::gameplay::Exfiltration decoded;
    EXPECT_NO_THROW(decoded = j.get<spy::gameplay::Exfiltration>());
    EXPECT_EQ(decoded, expected);
}