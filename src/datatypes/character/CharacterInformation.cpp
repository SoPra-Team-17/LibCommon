//
// Created by Carolin on 02.04.2020.
//

#include "CharacterInformation.hpp"

namespace spy::character {

    const util::UUID &CharacterInformation::getCharacterId() const {
        return characterId;
    }

    const CharacterDescription &CharacterInformation::getCharacter() const {
        return character;
    }

}   // namespace spy::character
