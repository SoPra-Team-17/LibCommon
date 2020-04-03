//
// Created by Carolin on 03.04.2020.
//

#include <gtest/gtest.h>
#include <character/Character.hpp>

TEST(character, Character) {
    std::string s = "some Name";
    spy::util::UUID u = {};
    spy::character::Character c = {u, s};
    EXPECT_EQ(c.getName(), s);
    EXPECT_EQ(c.getMp(), 0);
    EXPECT_EQ(c.getAp(), 0);
    EXPECT_EQ(c.getHp(), 100);
    EXPECT_EQ(c.getIp(), 0);
    EXPECT_EQ(c.getChips(), 10);
}
