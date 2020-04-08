/**
 * @file   CharacterInformation.cpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Definition of the character information class.
 */

#include "CharacterInformation.hpp"

namespace spy::character {

    CharacterInformation::CharacterInformation() : characterId{}, character{} {}

    CharacterInformation::CharacterInformation(const util::UUID &characterId, const CharacterDescription &character) :
            characterId(characterId), character(character) {}

    const util::UUID &CharacterInformation::getCharacterId() const {
        return characterId;
    }

    const CharacterDescription &CharacterInformation::getCharacter() const {
        return character;
    }

    void from_json(const nlohmann::json &/*j*/, CharacterInformation &/*c*/) {
        // TODO CharacterInformation from_json
    }

    void to_json(nlohmann::json &/*j*/, const CharacterInformation &/*c*/) {
        // TODO CharacterInformation from_json
    }
}   // namespace spy::character
