//
// Created by Carolin on 02.04.2020.
//

#ifndef LIBCOMMON_SRC_DATATYPES_CHARACTER_CHARACTERINFORMATION_HPP_
#define LIBCOMMON_SRC_DATATYPES_CHARACTER_CHARACTERINFORMATION_HPP_

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

    // getter and setter
    [[nodiscard]] const util::UUID &getCharacterId() const;

    [[nodiscard]] const CharacterDescription &getCharacter() const;


   private:
    const spy::util::UUID characterId;
    const CharacterDescription character;
  };

}

#endif //LIBCOMMON_SRC_DATATYPES_CHARACTER_CHARACTERINFORMATION_HPP_
