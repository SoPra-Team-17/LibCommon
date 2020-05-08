//
// Created by jonas on 02.04.20.
//
#include <gtest/gtest.h>
#include "datatypes/gadgets/Gadget.hpp"
#include "util/GadgetSerialization.hpp"

TEST(JSON_Encode, Gadget_generic) {
    auto rocketPen = std::make_shared<spy::gadget::Gadget>(spy::gadget::GadgetEnum::ROCKET_PEN);
    rocketPen->setUsagesLeft(7);

    nlohmann::json rocketPenJson = rocketPen;

    std::string serialized = rocketPenJson.dump();
    std::string expected = R"({"GadgetEnum":"ROCKET_PEN","usages":7})";
    EXPECT_EQ(expected, serialized);
}
