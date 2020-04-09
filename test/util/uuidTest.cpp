
#include <gtest/gtest.h>
#include <util/UUID.hpp>
#include <nlohmann/json.hpp>

TEST(UUID, default_null) {
    spy::util::UUID u;
    EXPECT_TRUE(u.isNull());
}

TEST(UUID, generate_notnull) {
    auto u = spy::util::UUID::generate();
    EXPECT_FALSE(u.isNull());
}

TEST(UUID, clear_null) {
    auto u = spy::util::UUID::generate();
    u.clear();
    EXPECT_TRUE(u.isNull());
}

TEST(UUID, serializeJson) {
    auto u = spy::util::UUID::generate();
    nlohmann::json j;
    EXPECT_NO_THROW(j = u);
}

TEST(UUID, deserializeJson) {
    std::string uuidText = "6a1333d0-2317-4044-9d37-047d29205011";
    auto json = nlohmann::json::parse("\"" + uuidText + "\"");
    spy::util::UUID u;
    EXPECT_NO_THROW(u = json.get<spy::util::UUID>());
    EXPECT_FALSE(u.isNull());
    EXPECT_EQ(u.to_string_lower(), uuidText);
}