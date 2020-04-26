//
// Created by jonas on 26.04.20.
//

#include <gtest/gtest.h>
#include <datatypes/character/CharacterSet.hpp>

class CharacterSet : public ::testing::Test {
    protected:
        spy::character::CharacterSet set;
        spy::character::Character c1 = {spy::util::UUID::generate(), "Hans Wurst"};
        spy::character::Character c1_copy = {c1.getCharacterId(), "Not Hans Wurst"};
        spy::character::Character c2 = {spy::util::UUID::generate(), "James Bond"};
};

TEST_F(CharacterSet, construct_valid) {
    auto characterSet = spy::character::CharacterSet{c1, c2};
    EXPECT_EQ(characterSet.size(), 2);
}

TEST_F(CharacterSet, construct_invalid) {
    auto characterSet = spy::character::CharacterSet{c1, c1_copy};
    EXPECT_EQ(characterSet.size(), 1);
    // Expect the first element in initializer list to be used, not the second (with identical UUID)
    EXPECT_EQ(characterSet.findByUUID(c1.getCharacterId())->getName(), c1.getName());
}

TEST_F(CharacterSet, insert_valid) {
    auto result = set.insert(c1);
    EXPECT_TRUE(result.second);

    result = set.insert(c2);
    EXPECT_TRUE(result.second);
    EXPECT_EQ(set.size(), 2);
}

TEST_F(CharacterSet, insert_valid_move) {
    auto result = set.insert(std::move(c1));
    EXPECT_TRUE(result.second);

    result = set.insert(std::move(c2));
    EXPECT_TRUE(result.second);
    EXPECT_EQ(set.size(), 2);
}

TEST_F(CharacterSet, emplace_valid_move) {
    auto result = set.emplace(c1.getCharacterId(), c1.getName());
    EXPECT_TRUE(result.second);

    result = set.emplace(c2.getCharacterId(), c2.getName());
    EXPECT_TRUE(result.second);
    EXPECT_EQ(set.size(), 2);
}

TEST_F(CharacterSet, insert_same) {
    set.insert(c1);

    auto result = set.insert(c1);
    EXPECT_FALSE(result.second);
    EXPECT_EQ(set.size(), 1);
}

TEST_F(CharacterSet, insert_sameUUID) {
    set.insert(c1);

    auto result = set.insert(c1_copy);
    EXPECT_FALSE(result.second);
    EXPECT_EQ(set.size(), 1);
}

TEST_F(CharacterSet, insert_sameUUID_move) {
    set.insert(std::move(c1));

    auto result = set.insert(std::move(c1_copy));
    EXPECT_FALSE(result.second);
    EXPECT_EQ(set.size(), 1);
}

TEST_F(CharacterSet, emplace_sameUUID) {
    set.emplace(c1.getCharacterId(), c1.getName());

    auto result = set.emplace(c1_copy.getCharacterId(), c1_copy.getName());
    EXPECT_FALSE(result.second);
    EXPECT_EQ(set.size(), 1);
}

TEST_F(CharacterSet, get_uuid_modify) {
    set.insert(c1);

    auto c = set.getByUUID(c1.getCharacterId());
    c->setCoordinates({1, 7});
    EXPECT_EQ(set.findByUUID(c1.getCharacterId())->getCoordinates(), (spy::util::Point{1, 7}));
}

TEST_F(CharacterSet, iterate_modify) {
    set.insert(c1);
    set.insert(c2);

    for (auto &c:set) {
        c.setChips(1'000'000);
    }

    EXPECT_EQ(set.findByUUID(c1.getCharacterId())->getChips(), 1'000'000);
    EXPECT_EQ(set.findByUUID(c2.getCharacterId())->getChips(), 1'000'000);
}

TEST_F(CharacterSet, iterate_const) {
    set.insert(c1);
    set.insert(c2);

    const auto constset = set;

    int i = 0;
    spy::character::CharacterSet s;
    for (const auto &c:constset) {
        s.insert(c);
    }
    EXPECT_EQ(set, s);
}