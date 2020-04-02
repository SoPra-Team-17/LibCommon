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
    // TODO constructor

    // getter and setter
    [[nodiscard]] const util::UUID &getCharacterId() const {
      return characterId;
    }
    void setCharacterId(const util::UUID &character_id) {
      characterId = character_id;
    }
    [[nodiscard]] const CharacterDescription &getCharacter() const {
      return character;
    }
    void setCharacter(const CharacterDescription &characterdescription) {
      CharacterInformation::character = characterdescription;
    }

   private:
    spy::util::UUID characterId;
    CharacterDescription character;
  };

}

#endif //LIBCOMMON_SRC_DATATYPES_CHARACTER_CHARACTERINFORMATION_HPP_
