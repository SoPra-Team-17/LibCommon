//
// Created by jonas on 10.04.20.
//

#include <gtest/gtest.h>
#include <network/messages/ItemChoice.hpp>

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

TEST(messages, ItemChoiceMessage_encode_character) {
    spy::network::messages::ItemChoice characterChoice(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"},
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655441111"});

    nlohmann::json j;
    EXPECT_NO_THROW(j = characterChoice);
    EXPECT_EQ(j.dump(),
              R"({"chosenCharacter":"123e4567-e89b-12d3-a456-426655441111","chosenGadget":null,"creationDate":")" +
              characterChoice.getCreationDate() + R"(","playerId":"123e4567-e89b-12d3-a456-426655440000","type":"ITEM_CHOICE"})");
}

TEST(messages, ItemChoiceMessage_encode_gadget) {
    spy::network::messages::ItemChoice gadgetChoice(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"},
            spy::gadget::GadgetEnum::POISON_PILLS);

    nlohmann::json j;
    EXPECT_NO_THROW(j = gadgetChoice);
    EXPECT_EQ(j.dump(),
              R"({"chosenCharacter":null,"chosenGadget":"POISON_PILLS","creationDate":")" +
              gadgetChoice.getCreationDate() + R"(","playerId":"123e4567-e89b-12d3-a456-426655440000","type":"ITEM_CHOICE"})");
}

TEST(messages, ItemChoiceMessage_decode_character) {
    auto choice = spy::util::UUID{"123e4567-e89b-12d3-a456-426655441111"};
    spy::network::messages::ItemChoice expectedCharacterChoice(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"},
            choice);

    std::string input = R"({"chosenCharacter":"123e4567-e89b-12d3-a456-426655441111","chosenGadget":null,"creationDate":"","playerId":"123e4567-e89b-12d3-a456-426655440000","type":"ITEM_CHOICE"})";
    auto parsedJson = nlohmann::json::parse(input);

    spy::network::messages::ItemChoice decodedChoice;
    EXPECT_NO_THROW(decodedChoice = parsedJson.get<spy::network::messages::ItemChoice>());
    EXPECT_TRUE(std::holds_alternative<spy::util::UUID>(decodedChoice.getChoice()));
    EXPECT_EQ(choice, std::get<spy::util::UUID>(decodedChoice.getChoice()));
}

TEST(messages, ItemChoiceMessage_decode_gadget) {
    auto choice = spy::gadget::GadgetEnum::POISON_PILLS;
    spy::network::messages::ItemChoice expectedGadgetChoice(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"},
            choice);

    std::string input = R"({"chosenCharacter":null,"chosenGadget":"POISON_PILLS","creationDate":"","playerId":"123e4567-e89b-12d3-a456-426655440000","type":"ITEM_CHOICE"})";
    auto parsedJson = nlohmann::json::parse(input);

    spy::network::messages::ItemChoice decodedChoice;
    EXPECT_NO_THROW(decodedChoice = parsedJson.get<spy::network::messages::ItemChoice>());
    EXPECT_TRUE(std::holds_alternative<spy::gadget::GadgetEnum>(decodedChoice.getChoice()));
    EXPECT_EQ(choice, std::get<spy::gadget::GadgetEnum>(decodedChoice.getChoice()));
}