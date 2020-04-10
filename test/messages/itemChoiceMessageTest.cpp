//
// Created by jonas on 10.04.20.
//

#include <gtest/gtest.h>
#include <network/messages/ItemChoice.hpp>

TEST(messages, ItemChoiceMessage_encode_character) {
    spy::network::messages::ItemChoice characterChoice(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"},
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655441111"});

    nlohmann::json j;
    EXPECT_NO_THROW(j = characterChoice);
    EXPECT_EQ(j.dump(),
              R"({"chosenCharacter":"123e4567-e89b-12d3-a456-426655441111","chosenGadget":null,"creationDate":"","playerId":"123e4567-e89b-12d3-a456-426655440000","type":"ITEM_CHOICE"})");
}

TEST(messages, ItemChoiceMessage_encode_gadget) {
    spy::network::messages::ItemChoice gadgetChoice(
            spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"},
            spy::gadget::GadgetEnum::POISON_PILLS);

    nlohmann::json j;
    EXPECT_NO_THROW(j = gadgetChoice);
    EXPECT_EQ(j.dump(),
              R"({"chosenCharacter":null,"chosenGadget":"POISON_PILLS","creationDate":"","playerId":"123e4567-e89b-12d3-a456-426655440000","type":"ITEM_CHOICE"})");
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