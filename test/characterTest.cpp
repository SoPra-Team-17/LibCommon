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
    EXPECT_EQ(c.getMovePoints(), 0);
    EXPECT_EQ(c.getActionPoints(), 0);
    EXPECT_EQ(c.getHealthPoints(), 100);
    EXPECT_EQ(c.getIntelligencePoints(), 0);
    EXPECT_EQ(c.getChips(), 10);
}
