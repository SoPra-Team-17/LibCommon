//
// Created by Carolin on 03.04.2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <character/Character.hpp>
#include <character/CharacterDescription.hpp>
#include <character/CharacterInformation.hpp>

TEST(Character, Character) {
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

TEST(Character, json_encode) {
    spy::character::Character character({}, "James Bond");
    character.setProperties({spy::character::PropertyEnum::SPRYNESS,
                             spy::character::PropertyEnum::TOUGHNESS,
                             spy::character::PropertyEnum::ROBUST_STOMACH,
                             spy::character::PropertyEnum::LUCKY_DEVIL,
                             spy::character::PropertyEnum::TRADECRAFT});

    nlohmann::json characterJson = character;

    std::string serialized = characterJson.dump();
    std::string expected = R"({"ap":0,"characterId":"00000000-0000-0000-0000-000000000000","chips":10,"coordinates":{"x":0,"y":0},"features":["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"],"gadgets":[],"hp":100,"ip":0,"mp":0,"name":"James Bond"})";
    EXPECT_EQ(expected, serialized);
}

TEST(Character, json_decode) {
    auto input = R"({"ap":0,"characterId":"00000000-0000-0000-0000-000000000000","chips":10,"coordinates":{"x":0,"y":0},"features":["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"],"gadgets":[],"hp":100,"ip":0,"mp":0,"name":"James Bond"})"_json;
    auto decodedCharacter = input.get<spy::character::Character>();

    spy::character::Character character({}, "James Bond");
    character.setProperties({spy::character::PropertyEnum::SPRYNESS,
                             spy::character::PropertyEnum::TOUGHNESS,
                             spy::character::PropertyEnum::ROBUST_STOMACH,
                             spy::character::PropertyEnum::LUCKY_DEVIL,
                             spy::character::PropertyEnum::TRADECRAFT});

    EXPECT_EQ(character.getCharacterId().to_string(), decodedCharacter.getCharacterId().to_string());
    EXPECT_EQ(character.getName(), decodedCharacter.getName());
    EXPECT_EQ(character.getCoordinates(), decodedCharacter.getCoordinates());
    EXPECT_EQ(character.getMovePoints(), decodedCharacter.getMovePoints());
    EXPECT_EQ(character.getActionPoints(), decodedCharacter.getActionPoints());
    EXPECT_EQ(character.getHealthPoints(), decodedCharacter.getHealthPoints());
    EXPECT_EQ(character.getIntelligencePoints(), decodedCharacter.getIntelligencePoints());
    EXPECT_EQ(character.getChips(), decodedCharacter.getChips());
    EXPECT_EQ(character.getProperties(), decodedCharacter.getProperties());
    EXPECT_TRUE(character.getGadgets().empty());
}

TEST(CharacterDescription, json_encode) {
    spy::character::CharacterDescription characterDescription("James Bond", "Bester Geheimagent aller Zeiten mit 00-Status.",
            spy::character::GenderEnum::DIVERSE, {spy::character::PropertyEnum::SPRYNESS,
                                                  spy::character::PropertyEnum::TOUGHNESS,
                                                  spy::character::PropertyEnum::ROBUST_STOMACH,
                                                  spy::character::PropertyEnum::LUCKY_DEVIL,
                                                  spy::character::PropertyEnum::TRADECRAFT});

    nlohmann::json characterDescriptionJson = characterDescription;

    std::string serialized = characterDescriptionJson.dump();
    std::string expected = R"({"description":"Bester Geheimagent aller Zeiten mit 00-Status.","features":["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"],"gender":"DIVERSE","name":"James Bond"})";
    EXPECT_EQ(expected, serialized);
}

TEST(CharacterDescription, json_decode) {
    auto input = R"({"description":"Bester Geheimagent aller Zeiten mit 00-Status.","features":["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"],"gender":"DIVERSE","name":"James Bond"})"_json;
    auto decodedCharacterDescription = input.get<spy::character::CharacterDescription>();

    spy::character::CharacterDescription characterDescription ("James Bond",
            "Bester Geheimagent aller Zeiten mit 00-Status.", spy::character::GenderEnum::DIVERSE,
            {spy::character::PropertyEnum::SPRYNESS, spy::character::PropertyEnum::TOUGHNESS,
             spy::character::PropertyEnum::ROBUST_STOMACH, spy::character::PropertyEnum::LUCKY_DEVIL,
             spy::character::PropertyEnum::TRADECRAFT});

    EXPECT_EQ(characterDescription.getName(), decodedCharacterDescription.getName());
    EXPECT_EQ(characterDescription.getDescription(), decodedCharacterDescription.getDescription());
    EXPECT_EQ(characterDescription.getGender(), decodedCharacterDescription.getGender());
    EXPECT_EQ(characterDescription.getFeatures(), decodedCharacterDescription.getFeatures());
}

TEST(CharacterInformation, json_encode) {
    spy::character::CharacterInformation characterInformation({},
            {"James Bond","Bester Geheimagent aller Zeiten mit 00-Status.", spy::character::GenderEnum::DIVERSE,
             {spy::character::PropertyEnum::SPRYNESS, spy::character::PropertyEnum::TOUGHNESS,
              spy::character::PropertyEnum::ROBUST_STOMACH, spy::character::PropertyEnum::LUCKY_DEVIL,
              spy::character::PropertyEnum::TRADECRAFT}});

    nlohmann::json characterInformationJson = characterInformation;

    std::string serialized = characterInformationJson.dump();
    std::string expected = R"({"character":{"description":"Bester Geheimagent aller Zeiten mit 00-Status.","features":["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"],"gender":"DIVERSE","name":"James Bond"},"characterId":"00000000-0000-0000-0000-000000000000"})";
    EXPECT_EQ(expected, serialized);
}

TEST(CharacterInformation, json_decode) {
    auto input = R"({"character":{"description":"Bester Geheimagent aller Zeiten mit 00-Status.","features":["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"],"gender":"DIVERSE","name":"James Bond"},"characterId":"00000000-0000-0000-0000-000000000000"})"_json;
    auto decodedCharacterInformation = input.get<spy::character::CharacterInformation>();

    spy::character::CharacterInformation characterInformation({},
            {"James Bond","Bester Geheimagent aller Zeiten mit 00-Status.", spy::character::GenderEnum::DIVERSE,
             {spy::character::PropertyEnum::SPRYNESS, spy::character::PropertyEnum::TOUGHNESS,
              spy::character::PropertyEnum::ROBUST_STOMACH, spy::character::PropertyEnum::LUCKY_DEVIL,
              spy::character::PropertyEnum::TRADECRAFT}});

    EXPECT_EQ(characterInformation.getCharacterId().to_string(), decodedCharacterInformation.getCharacterId().to_string());
    EXPECT_EQ(characterInformation.getCharacter().getName(), decodedCharacterInformation.getCharacter().getName());
    EXPECT_EQ(characterInformation.getCharacter().getDescription(), decodedCharacterInformation.getCharacter().getDescription());
    EXPECT_EQ(characterInformation.getCharacter().getGender(), decodedCharacterInformation.getCharacter().getGender());
    EXPECT_EQ(characterInformation.getCharacter().getFeatures(), decodedCharacterInformation.getCharacter().getFeatures());
}
