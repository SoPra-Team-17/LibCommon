//
// Created by jonas on 02.04.20.
//
#include <gtest/gtest.h>
#include <datatypes/gadgets/Cocktail.hpp>
#include <datatypes/gadgets/WiretapWithEarplugs.hpp>

TEST(Gadgets, cocktail_type) {
    spy::gadget::Cocktail c;
    EXPECT_EQ(c.getType(), spy::gadget::GadgetEnum::COCKTAIL);
}

TEST(Gadgets, wiretap_type) {
    spy::gadget::WiretapWithEarplugs c;
    EXPECT_EQ(c.getType(), spy::gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS);
}
