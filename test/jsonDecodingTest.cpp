//
// Created by jonas on 02.04.20.
//
#include <gtest/gtest.h>
#include <Gadget.hpp>

TEST(JSON_Decode, Gadget_generic) {
    using namespace spy::gadget;
    auto input = R"({"GadgetEnum":"ROCKET_PEN","usages":7})"_json;
    auto decodedGadget = input.get<Gadget>();

    Gadget rocketPen(GadgetEnum::ROCKET_PEN);
    rocketPen.setUsagesLeft(7);

    EXPECT_EQ(rocketPen.getType(), decodedGadget.getType());
    EXPECT_EQ(rocketPen.getUsagesLeft(), decodedGadget.getUsagesLeft());
}

TEST(JSON_Decode, Gadget_invalid_type) {
    using namespace spy::gadget;
    auto input = R"({"GadgetEnum":"COVID19","usages":7787451207})"_json;
    auto decodedGadget = input.get<Gadget>();

    EXPECT_EQ(decodedGadget.getType(), GadgetEnum::INVALID);
}

TEST(JSON_Decode, Gadget_invalid_keys) {
    using namespace spy::gadget;
    auto input = R"({"NotTheEnum":"ROCKET_PEN","usagesLeft":-5})"_json;
    EXPECT_ANY_THROW(input.get<Gadget>());
}
