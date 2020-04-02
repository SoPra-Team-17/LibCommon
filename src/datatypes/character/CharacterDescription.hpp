//
// Created by Carolin on 02.04.2020.
//

#ifndef LIBCOMMON_SRC_DATATYPES_CHARACTER_CHARACTERDESCRIPTION_HPP_
#define LIBCOMMON_SRC_DATATYPES_CHARACTER_CHARACTERDESCRIPTION_HPP_

#include <string>
#include <list>
#include <datatypes/character/Character.hpp>

namespace spy::character {
  enum class GenderEnum {
    MALE,
    FEMALE,
    DIVERSE
  };

  class CharacterDescription {
   public:
    // TODO constructor

    // getter and setter
    [[nodiscard]] const std::string &getName() const {
      return name;
    }
    void setName(const std::string &n) {
      CharacterDescription::name = n;
    }
    [[nodiscard]] const std::string &getDescription() const {
      return description;
    }
    void setDescription(const std::string &descript) {
      CharacterDescription::description = descript;
    }
    [[nodiscard]] GenderEnum getGender() const {
      return gender;
    }
    void setGender(GenderEnum gend) {
      CharacterDescription::gender = gend;
    }
    [[nodiscard]] const std::list<spy::character::PropertyEnum> &getFeatures() const {
      return features;
    }
    void setFeatures(const std::list<spy::character::PropertyEnum> &propertylist) {
      CharacterDescription::features = propertylist;
    }

   private:
    std::string name;
    std::string description;
    GenderEnum gender;
    std::list<spy::character::PropertyEnum> features;
  };
}

#endif //LIBCOMMON_SRC_DATATYPES_CHARACTER_CHARACTERDESCRIPTION_HPP_
