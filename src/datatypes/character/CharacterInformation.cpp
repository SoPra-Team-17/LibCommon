//
// Created by Carolin on 02.04.2020.
//

#include "CharacterInformation.hpp"

namespace spy::character{

    const spy::util::UUID &spy::character::CharacterInformation::getCharacterId() const {
        return characterId;
    }

    const spy::character::CharacterDescription &spy::character::CharacterInformation::getCharacter() const {
        return character;
    }

}   // namespace spy::character