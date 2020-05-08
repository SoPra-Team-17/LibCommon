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
#include <network/messages/RequestGamePause.hpp>
#include <network/messages/GameLeave.hpp>
#include <network/messages/RequestMetaInformation.hpp>

TEST(messages, helloMessage_validate) {
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

TEST(messages, reconnecMessage_validate) {
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

    spy::network::messages::ItemChoice noChoice(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655444444"},
            {});

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

    EXPECT_FALSE(noChoice.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
}

TEST(messages, EquipmentChoiceMessage_validate) {
    std::vector<spy::util::UUID> offeredCharacters{
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"},
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"}};
    std::vector<spy::gadget::GadgetEnum> offeredGadgets{
            spy::gadget::GadgetEnum::BOWLER_BLADE,
            spy::gadget::GadgetEnum::CHICKEN_FEED};

    std::map<spy::util::UUID, std::set<spy::gadget::GadgetEnum>> mapCor1{
            {spy::util::UUID{
                    "123e4567-e89b-12d3-a456-426655440001"},          {spy::gadget::GadgetEnum::BOWLER_BLADE, spy::gadget::GadgetEnum::CHICKEN_FEED}},
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"}, {}}
    };
    std::map<spy::util::UUID, std::set<spy::gadget::GadgetEnum>> mapCor2{
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"}, {spy::gadget::GadgetEnum::BOWLER_BLADE}},
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"}, {spy::gadget::GadgetEnum::CHICKEN_FEED}}
    };
    std::map<spy::util::UUID, std::set<spy::gadget::GadgetEnum>> mapCor3{
            {spy::util::UUID{
                    "123e4567-e89b-12d3-a456-426655440001"}, {spy::gadget::GadgetEnum::BOWLER_BLADE, spy::gadget::GadgetEnum::CHICKEN_FEED}}
    };
    std::map<spy::util::UUID, std::set<spy::gadget::GadgetEnum>> mapFalse1{
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"}, {spy::gadget::GadgetEnum::BOWLER_BLADE}},
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"}, {}}
    };
    std::map<spy::util::UUID, std::set<spy::gadget::GadgetEnum>> mapFalse2{
            {spy::util::UUID{
                    "123e4567-e89b-12d3-a456-426655440001"},          {spy::gadget::GadgetEnum::BOWLER_BLADE, spy::gadget::GadgetEnum::CHICKEN_FEED}},
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"}, {spy::gadget::GadgetEnum::BOWLER_BLADE}}
    };
    std::map<spy::util::UUID, std::set<spy::gadget::GadgetEnum>> mapFalse3{
            {spy::util::UUID{
                    "123e4567-e89b-12d3-a456-426655440005"},          {spy::gadget::GadgetEnum::CHICKEN_FEED}},
            {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440001"}, {spy::gadget::GadgetEnum::BOWLER_BLADE}}
    };

    spy::network::messages::EquipmentChoice mCor1(spy::util::UUID{}, mapCor1);
    spy::network::messages::EquipmentChoice mCor2(spy::util::UUID{}, mapCor2);
    spy::network::messages::EquipmentChoice mCor3(spy::util::UUID{}, mapCor3);
    spy::network::messages::EquipmentChoice mFalse1(spy::util::UUID{}, mapFalse1);
    spy::network::messages::EquipmentChoice mFalse2(spy::util::UUID{}, mapFalse2);
    spy::network::messages::EquipmentChoice mFalse3(spy::util::UUID{}, mapFalse3);

    EXPECT_TRUE(mCor1.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_TRUE(mCor1.validate(spy::network::RoleEnum::AI, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mCor1.validate(spy::network::RoleEnum::INVALID, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mCor1.validate(spy::network::RoleEnum::SPECTATOR, offeredCharacters, offeredGadgets));

    EXPECT_TRUE(mCor2.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mCor2.validate(spy::network::RoleEnum::SPECTATOR, offeredCharacters, offeredGadgets));

    EXPECT_TRUE(mCor3.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mCor3.validate(spy::network::RoleEnum::SPECTATOR, offeredCharacters, offeredGadgets));

    EXPECT_FALSE(mFalse1.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mFalse1.validate(spy::network::RoleEnum::AI, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mFalse1.validate(spy::network::RoleEnum::INVALID, offeredCharacters, offeredGadgets));
    EXPECT_FALSE(mFalse1.validate(spy::network::RoleEnum::SPECTATOR, offeredCharacters, offeredGadgets));

    EXPECT_FALSE(mFalse2.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));

    EXPECT_FALSE(mFalse3.validate(spy::network::RoleEnum::PLAYER, offeredCharacters, offeredGadgets));
}


TEST(messages, RequestReplayMessage_validate) {
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


TEST(messages, RequestGamePauseMessage_validate) {
    using namespace spy::network;
    using namespace spy::network::messages;

    RequestGamePause mPause(spy::util::UUID{}, true);
    RequestGamePause mNoPause(spy::util::UUID{}, false);

    EXPECT_TRUE(mPause.validate(RoleEnum::PLAYER, false, false));
    EXPECT_FALSE(mPause.validate(RoleEnum::SPECTATOR, false, false));
    EXPECT_FALSE(mPause.validate(RoleEnum::AI, false, false));
    EXPECT_FALSE(mPause.validate(RoleEnum::INVALID, false, false));

    EXPECT_FALSE(mPause.validate(RoleEnum::PLAYER, true, false));
    EXPECT_FALSE(mPause.validate(RoleEnum::PLAYER, true, true));

    EXPECT_TRUE(mNoPause.validate(RoleEnum::PLAYER, true, false));
    EXPECT_FALSE(mNoPause.validate(RoleEnum::SPECTATOR, true, false));
    EXPECT_FALSE(mNoPause.validate(RoleEnum::AI, true, false));
    EXPECT_FALSE(mNoPause.validate(RoleEnum::INVALID, true, false));

    EXPECT_FALSE(mNoPause.validate(RoleEnum::PLAYER, true, true));
    EXPECT_FALSE(mNoPause.validate(RoleEnum::PLAYER, false, false));
}

TEST(messages, GameLeaveMessage_validate) {
    using namespace spy::network;
    using namespace spy::network::messages;

    GameLeave m(spy::util::UUID{});

    EXPECT_TRUE(m.validate(RoleEnum::PLAYER));
    EXPECT_TRUE(m.validate(RoleEnum::AI));
    EXPECT_TRUE(m.validate(RoleEnum::SPECTATOR));
    EXPECT_FALSE(m.validate(RoleEnum::INVALID));
}

TEST(messages, RequestMetaInformationMessage_validate) {
    using namespace spy::network;
    using namespace spy::network::messages;

    std::vector<MetaInformationKey> corKeys{MetaInformationKey::SPECTATOR_COUNT,
                                            MetaInformationKey::SPECTATOR_MEMBERS,
                                            MetaInformationKey::CONFIGURATION_SCENARIO,
                                            MetaInformationKey::CONFIGURATION_MATCH_CONFIG,
                                            MetaInformationKey::CONFIGURATION_CHARACTER_INFORMATION,
                                            MetaInformationKey::GAME_REMAINING_PAUSE_TIME,
                                            MetaInformationKey::FACTION_PLAYER1,
                                            MetaInformationKey::FACTION_PLAYER2,
                                            MetaInformationKey::FACTION_NEUTRAL,
                                            MetaInformationKey::GADGETS_PLAYER1,
                                            MetaInformationKey::GADGETS_PLAYER2};

    std::vector<MetaInformationKey> falseKeys{MetaInformationKey::INVALID,
                                              MetaInformationKey::SPECTATOR_COUNT,
                                              MetaInformationKey::SPECTATOR_MEMBERS,
                                              MetaInformationKey::CONFIGURATION_SCENARIO,
                                              MetaInformationKey::CONFIGURATION_MATCH_CONFIG,
                                              MetaInformationKey::CONFIGURATION_CHARACTER_INFORMATION,
                                              MetaInformationKey::GAME_REMAINING_PAUSE_TIME,
                                              MetaInformationKey::FACTION_PLAYER1,
                                              MetaInformationKey::FACTION_PLAYER2,
                                              MetaInformationKey::FACTION_NEUTRAL,
                                              MetaInformationKey::GADGETS_PLAYER1,
                                              MetaInformationKey::GADGETS_PLAYER2};

    RequestMetaInformation mCor(spy::util::UUID{}, corKeys);
    RequestMetaInformation mFalse(spy::util::UUID{}, falseKeys);

    EXPECT_TRUE(mCor.validate(RoleEnum::PLAYER));
    EXPECT_TRUE(mCor.validate(RoleEnum::AI));
    EXPECT_TRUE(mCor.validate(RoleEnum::SPECTATOR));
    EXPECT_FALSE(mCor.validate(RoleEnum::INVALID));

    EXPECT_FALSE(mFalse.validate(RoleEnum::PLAYER));
    EXPECT_FALSE(mFalse.validate(RoleEnum::AI));
    EXPECT_FALSE(mFalse.validate(RoleEnum::SPECTATOR));
    EXPECT_FALSE(mFalse.validate(RoleEnum::INVALID));
}
