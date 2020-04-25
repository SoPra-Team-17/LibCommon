//
// Created by Carolin on 25.04.2020.
//

#include <gtest/gtest.h>
#include <network/messages/Hello.hpp>
#include <datatypes/gadgets/GadgetEnum.hpp>
#include <network/messages/ItemChoice.hpp>
#include <network/messages/Reconnect.hpp>
#include <network/messages/EquipmentChoice.hpp>
#include <network/messages/RequestReplay.hpp>

TEST(messages, helloMessage_validate){
    using namespace spy::network;
    using namespace spy::network::messages;

    Hello mCor1(spy::util::UUID(), "name123", RoleEnum::PLAYER);
    Hello mCor2(spy::util::UUID(), "name123", RoleEnum::AI);
    Hello mCor3(spy::util::UUID(), "name123", RoleEnum::SPECTATOR);
    Hello mFalse(spy::util::UUID(), "name123", RoleEnum::INVALID);

    EXPECT_TRUE(mCor1.validate());
    EXPECT_TRUE(mCor2.validate());
    EXPECT_TRUE(mCor3.validate());
    EXPECT_FALSE(mFalse.validate());
}

TEST(messages, reconnecMessage_validate){
    using namespace spy::network;
    using namespace spy::network::messages;

    Reconnect m(spy::util::UUID{}, spy::util::UUID{});

    EXPECT_TRUE(m.validate(RoleEnum::PLAYER));
    EXPECT_TRUE(m.validate(RoleEnum::AI));
    EXPECT_FALSE(m.validate(RoleEnum::SPECTATOR));
    EXPECT_FALSE(m.validate(RoleEnum::INVALID));
}


TEST(messages, ItemChoiceMessage_validate) {
    std::vector<spy::util::UUID> offeredCharacters{
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"},
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"}};
    std::vector<spy::gadget::GadgetEnum> offeredGadgets{
            spy::gadget::GadgetEnum::BOWLER_BLADE,
            spy::gadget::GadgetEnum::CHICKEN_FEED};

    spy::network::messages::ItemChoice characterChoiceCor1(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655444444"},
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"});

    spy::network::messages::ItemChoice characterChoiceCor2(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655444444"},
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"});

    spy::network::messages::ItemChoice characterChoiceFalse(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655444444"},
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440011"});

    spy::network::messages::ItemChoice gadgetChoiceCor1(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655444444"},
            spy::gadget::GadgetEnum::BOWLER_BLADE);

    spy::network::messages::ItemChoice gadgetChoiceCor2(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655444444"},
            spy::gadget::GadgetEnum::CHICKEN_FEED);

    spy::network::messages::ItemChoice gadgetChoiceFalse(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655444444"},
            spy::gadget::GadgetEnum::POISON_PILLS);

    EXPECT_TRUE(characterChoiceCor1.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_TRUE(characterChoiceCor2.validate(spy::network::RoleEnum::AI, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(characterChoiceFalse.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(characterChoiceCor1.validate(spy::network::RoleEnum::INVALID, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(characterChoiceCor1.validate(spy::network::RoleEnum::SPECTATOR, offeredCharacters, offeredGadgets));

    EXPECT_TRUE(gadgetChoiceCor1.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_TRUE(gadgetChoiceCor2.validate(spy::network::RoleEnum::AI, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(gadgetChoiceFalse.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(gadgetChoiceCor1.validate(spy::network::RoleEnum::INVALID, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(gadgetChoiceCor1.validate(spy::network::RoleEnum::SPECTATOR, offeredCharacters, offeredGadgets));
}

TEST(messages, EquipmentChoiceMessage_validate) {
    std::vector<spy::util::UUID> offeredCharacters{
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"},
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"}};
    std::vector<spy::gadget::GadgetEnum> offeredGadgets{
            spy::gadget::GadgetEnum::BOWLER_BLADE,
            spy::gadget::GadgetEnum::CHICKEN_FEED};

    std::map<spy::util::UUID, std::set<spy::gadget::GadgetEnum>> mapCor1 {
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"}, {spy::gadget::GadgetEnum::BOWLER_BLADE, spy::gadget::GadgetEnum::CHICKEN_FEED}},
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"}, {}}
    };std::map<spy::util::UUID, std::set<spy::gadget::GadgetEnum>> mapCor2 {
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"}, {spy::gadget::GadgetEnum::BOWLER_BLADE}},
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"}, {spy::gadget::GadgetEnum::CHICKEN_FEED}}
    };
    std::map<spy::util::UUID, std::set<spy::gadget::GadgetEnum>> mapFalse1 {
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"}, {spy::gadget::GadgetEnum::BOWLER_BLADE, spy::gadget::GadgetEnum::CHICKEN_FEED}}
    };
    std::map<spy::util::UUID, std::set<spy::gadget::GadgetEnum>> mapFalse2 {
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"}, {spy::gadget::GadgetEnum::BOWLER_BLADE}},
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"}, {}}
    };
    std::map<spy::util::UUID, std::set<spy::gadget::GadgetEnum>> mapFalse3 {
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"}, {spy::gadget::GadgetEnum::BOWLER_BLADE, spy::gadget::GadgetEnum::CHICKEN_FEED}},
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"}, {spy::gadget::GadgetEnum::BOWLER_BLADE}}
    };

    spy::network::messages::EquipmentChoice mCor1(spy::util::UUID{}, mapCor1);
    spy::network::messages::EquipmentChoice mCor2(spy::util::UUID{}, mapCor2);
    spy::network::messages::EquipmentChoice mFalse1(spy::util::UUID{}, mapFalse1);
    spy::network::messages::EquipmentChoice mFalse2(spy::util::UUID{}, mapFalse2);
    spy::network::messages::EquipmentChoice mFalse3(spy::util::UUID{}, mapFalse3);

    EXPECT_TRUE(mCor1.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_TRUE(mCor1.validate(spy::network::RoleEnum::AI, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mCor1.validate(spy::network::RoleEnum::INVALID, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mCor1.validate(spy::network::RoleEnum::SPECTATOR, offeredCharacters, offeredGadgets));

    EXPECT_TRUE(mCor2.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mCor2.validate(spy::network::RoleEnum::SPECTATOR, offeredCharacters, offeredGadgets));

    EXPECT_FALSE(mFalse1.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mFalse1.validate(spy::network::RoleEnum::AI, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mFalse1.validate(spy::network::RoleEnum::INVALID, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mFalse1.validate(spy::network::RoleEnum::SPECTATOR, offeredCharacters, offeredGadgets));

    EXPECT_FALSE(mFalse2.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mFalse3.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
}


TEST(messages, RequestReplayMessage_validate){
    using namespace spy::network;
    using namespace spy::network::messages;

    RequestReplay m(spy::util::UUID{});

    EXPECT_TRUE(m.validate(RoleEnum::SPECTATOR, true));
    EXPECT_TRUE(m.validate(RoleEnum::PLAYER, true));
    EXPECT_FALSE(m.validate(RoleEnum::SPECTATOR, false));
    EXPECT_FALSE(m.validate(RoleEnum::PLAYER, false));
    EXPECT_FALSE(m.validate(RoleEnum::AI, true));
    EXPECT_FALSE(m.validate(RoleEnum::INVALID, true));
}
