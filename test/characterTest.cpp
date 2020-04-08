//
// Created by Carolin on 03.04.2020.
//

#include <gtest/gtest.h>
#include <character/Character.hpp>
#include <character/CharacterDescription.hpp>
#include <character/CharacterInformation.hpp>

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

TEST(JSON_Encode, Character) {
    // TODO: define character
    spy::character::Character character({}, "James Bond");

    nlohmann::json characterJson = character;

    std::string serialized = characterJson.dump();
    // TODO: define expected according to character
    std::string expected = R"({"charcterId":TODO,"name":"James Bond",
        "description": "Bester Geheimagent aller Zeiten mit 00-Status.","gender": "DIVERSE",
		"features": ["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"]})";
    EXPECT_EQ(expected, serialized);
}

TEST(JSON_Decode, Character) {
    // TODO: define input
    auto input = R"({"name":"James Bond",
        "description": "Bester Geheimagent aller Zeiten mit 00-Status.","gender": "DIVERSE",
		"features": ["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"]})"_json;
    auto decodedCharacter = input.get<spy::character::Character>();

    // TODO: define character according to input
    spy::character::Character character({}, "James Bond");

    EXPECT_EQ(character.getCharacterId(), decodedCharacter.getCharacterId());
    EXPECT_EQ(character.getName(), decodedCharacter.getName());
    EXPECT_EQ(character.getCoordinates(), decodedCharacter.getCoordinates());
    EXPECT_EQ(character.getMovePoints(), decodedCharacter.getMovePoints());
    EXPECT_EQ(character.getActionPoints(), decodedCharacter.getActionPoints());
    EXPECT_EQ(character.getHealthPoints(), decodedCharacter.getHealthPoints());
    EXPECT_EQ(character.getIntelligencePoints(), decodedCharacter.getIntelligencePoints());
    EXPECT_EQ(character.getChips(), decodedCharacter.getChips());
    EXPECT_EQ(character.getProperties(), decodedCharacter.getProperties());
    EXPECT_EQ(character.getGadgets(), decodedCharacter.getGadgets());
}

TEST(JSON_Encode, CharacterDescription) {
    spy::character::CharacterDescription characterDescription("James Bond", "Bester Geheimagent aller Zeiten mit 00-Status.",
            spy::character::GenderEnum::DIVERSE, {spy::character::PropertyEnum::SPRYNESS,
                                                  spy::character::PropertyEnum::TOUGHNESS,
                                                  spy::character::PropertyEnum::ROBUST_STOMACH,
                                                  spy::character::PropertyEnum::LUCKY_DEVIL,
                                                  spy::character::PropertyEnum::TRADECRAFT});

    nlohmann::json characterDescriptionJson = characterDescription;

    std::string serialized = characterDescriptionJson.dump();
    std::string expected = R"({"name":"James Bond",
        "description": "Bester Geheimagent aller Zeiten mit 00-Status.","gender": "DIVERSE",
		"features": ["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"]})";
    EXPECT_EQ(expected, serialized);
}

TEST(JSON_Decode, CharacterDescription) {
    auto input = R"({"name":"James Bond",
        "description": "Bester Geheimagent aller Zeiten mit 00-Status.","gender": "DIVERSE",
		"features": ["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"]})"_json;
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

TEST(JSON_Encode, CharacterInformation) {
    // TODO: define UUID in characterInformation
    spy::character::CharacterInformation characterInformation({},
            {"James Bond","Bester Geheimagent aller Zeiten mit 00-Status.", spy::character::GenderEnum::DIVERSE,
             {spy::character::PropertyEnum::SPRYNESS, spy::character::PropertyEnum::TOUGHNESS,
              spy::character::PropertyEnum::ROBUST_STOMACH, spy::character::PropertyEnum::LUCKY_DEVIL,
              spy::character::PropertyEnum::TRADECRAFT}});

    nlohmann::json characterInformationJson = characterInformation;

    std::string serialized = characterInformationJson.dump();
    // TODO: define expected UUID according to character
    std::string expected = R"({"name":"James Bond",
        "description": "Bester Geheimagent aller Zeiten mit 00-Status.","gender": "DIVERSE",
		"features": ["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"]})";
    EXPECT_EQ(expected, serialized);
}

TEST(JSON_Decode, CharacterInformation) {
    // TODO: define UUID in input
    auto input = R"({"name":"James Bond",
        "description": "Bester Geheimagent aller Zeiten mit 00-Status.","gender": "DIVERSE",
		"features": ["SPRYNESS","TOUGHNESS","ROBUST_STOMACH","LUCKY_DEVIL","TRADECRAFT"]})"_json;
    auto decodedCharacterInformation = input.get<spy::character::CharacterInformation>();

    // TODO: define UUID in characterInformation according to input
    spy::character::CharacterInformation characterInformation({},
            {"James Bond","Bester Geheimagent aller Zeiten mit 00-Status.", spy::character::GenderEnum::DIVERSE,
             {spy::character::PropertyEnum::SPRYNESS, spy::character::PropertyEnum::TOUGHNESS,
              spy::character::PropertyEnum::ROBUST_STOMACH, spy::character::PropertyEnum::LUCKY_DEVIL,
              spy::character::PropertyEnum::TRADECRAFT}});

    EXPECT_EQ(characterInformation.getCharacterId(), decodedCharacterInformation.getCharacterId());
    EXPECT_EQ(characterInformation.getCharacter(), decodedCharacterInformation.getCharacter());
}
