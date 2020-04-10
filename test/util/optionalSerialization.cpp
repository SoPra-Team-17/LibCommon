//
// Created by jonas on 10.04.20.
//

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <util/OptionalSerialization.hpp>

template<typename T>
class OptionalContainer {
    public:
        std::optional<T> optionalMember;

        friend void to_json(nlohmann::json &j, const OptionalContainer<T> &c) {
            j["optionalMember"] = c.optionalMember;
        }

        friend void from_json(const nlohmann::json &j, OptionalContainer<T> &c) {
            if (j.find("optionalMember") != j.end()) {
                j.at("optionalMember").get_to(c.optionalMember);
            }
        }
};

TEST(OptionalSerialization, serialization_value) {
    OptionalContainer<int> o;
    o.optionalMember = 1337;
    nlohmann::json j;
    EXPECT_NO_THROW(j = o);
    EXPECT_EQ(j.dump(), R"({"optionalMember":1337})");
}

TEST(OptionalSerialization, serialization_null_value) {
    OptionalContainer<int> o;
    nlohmann::json j;
    EXPECT_NO_THROW(j = o);
    EXPECT_EQ(j.dump(), R"({"optionalMember":null})");
}

TEST(OptionalSerialization, deserialization_value) {
    std::string input = R"({"optionalMember":1337})";
    auto j = nlohmann::json::parse(input);
    auto decoded = j.get<OptionalContainer<int>>();
    EXPECT_TRUE(decoded.optionalMember.has_value());
    EXPECT_EQ(decoded.optionalMember.value(), 1337);
}

TEST(OptionalSerialization, deserialization_null_value) {
    std::string input = R"({"optionalMember":null})";
    auto j = nlohmann::json::parse(input);
    OptionalContainer<int> o;
    EXPECT_NO_THROW(o = j.get<OptionalContainer<int>>());
    EXPECT_FALSE(o.optionalMember.has_value());
}

TEST(OptionalSerialization, deserialization_missing_key_value) {
    std::string input = R"({})";
    auto j = nlohmann::json::parse(input);
    OptionalContainer<int> o;
    EXPECT_NO_THROW(o = j.get<OptionalContainer<int>>());
    EXPECT_FALSE(o.optionalMember.has_value());
}