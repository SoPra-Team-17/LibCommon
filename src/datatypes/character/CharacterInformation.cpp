/**
 * @file   CharacterInformation.cpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Definition of the character information class.
 */

#include "CharacterInformation.hpp"

namespace spy::character {

    CharacterInformation::CharacterInformation(const util::UUID &characterId, const CharacterDescription &character) :
        characterId(characterId), character(character) {}

    const util::UUID &CharacterInformation::getCharacterId() const {
        return characterId;
    }

    const CharacterDescription &CharacterInformation::getCharacter() const {
        return character;
    }

    void to_json(nlohmann::json &j, const spy::character::CharacterInformation &ci) {
        j["characterId"] = ci.characterId;
        j["character"] = ci.character;
    }

    void from_json(const nlohmann::json &j, spy::character::CharacterInformation &ci) {
        j.at("characterId").get_to(ci.characterId);
        j.at("character").get_to(ci.character);
    }

}   // namespace spy::character
