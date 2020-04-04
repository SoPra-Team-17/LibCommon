//
// Created by Carolin on 02.04.2020.
//

#ifndef LIBCOMMON_CHARACTERINFORMATION_HPP
#define LIBCOMMON_CHARACTERINFORMATION_HPP

#include <util/UUID.hpp>
#include <string>
#include <list>
#include <datatypes/character/Character.hpp>
#include <datatypes/character/CharacterDescription.hpp>

namespace spy::character {
    class CharacterInformation {
    public:
        CharacterInformation(util::UUID &character_id, CharacterDescription &character) : characterId(
                character_id), character(character) {}

        [[nodiscard]] const util::UUID &getCharacterId() const;

        [[nodiscard]] const CharacterDescription &getCharacter() const;


    private:
        const spy::util::UUID characterId;
        const CharacterDescription character;
    };

}

#endif //LIBCOMMON_CHARACTERINFORMATION_HPP
