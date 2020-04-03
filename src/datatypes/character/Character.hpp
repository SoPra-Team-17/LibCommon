#include <utility>

//
// Created by Carolin on 02.04.2020.
//

#ifndef LIBCOMMON_SRC_DATATYPES_CHARACTER_CHARACTER_HPP_
#define LIBCOMMON_SRC_DATATYPES_CHARACTER_CHARACTER_HPP_

#include <string>
#include <list>
#include <util/Point.hpp>
#include <datatypes/gadgets/Gadget.hpp>
#include <datatypes/character/PropertyEnum.hpp>
#include <util/UUID.hpp>

namespace spy::character{
  class Character {
   public:
    // TODO constructor

    // setter and getter
    const util::UUID &getCharacterId() const {
      return characterId;
    }
    [[nodiscard]] const std::string &getName() const {
      return name;
    }
    [[nodiscard]] const spy::util::Point &getCoordinates() const {
      return coordinates;
    }
    void setCoordinates(const spy::util::Point &coordinate) {
      Character::coordinates = coordinate;
    }
    [[nodiscard]] int getMp() const {
      return mp;
    }
    void setMp(int movepoints) {
      Character::mp = movepoints;
    }
    [[nodiscard]] int getAp() const {
      return ap;
    }
    void setAp(int actionpoints) {
      Character::ap = actionpoints;
    }
    [[nodiscard]] int getHp() const {
      return hp;
    }
    void setHp(int healthpoints) {
      Character::hp = healthpoints;
    }
    [[nodiscard]] int getIp() const {
      return ip;
    }
    void setIp(int intelligencepoints) {
      Character::ip = intelligencepoints;
    }
    [[nodiscard]] int getChips() const {
      return chips;
    }
    void setChips(int chip) {
      Character::chips = chip;
    }
    [[nodiscard]] const std::list<spy::character::PropertyEnum> &getProperties() const {
      return properties;
    }
    void setProperties(const std::list<spy::character::PropertyEnum> &propertylist) {
      Character::properties = propertylist;
    }
    [[nodiscard]] const std::list<spy::gadget::Gadget> &getGadgets() const {
      return gadgets;
    }
    void setGadgets(const std::list<spy::gadget::Gadget> &gadgetlist) {
      Character::gadgets = gadgetlist;
    }

   private:
    const spy::util::UUID characterId;
    const std::string name;
    spy::util::Point coordinates;
    int mp;
    int ap;
    int hp;
    int ip;
    int chips;
    std::list<PropertyEnum> properties;
    std::list<spy::gadget::Gadget> gadgets;
  };
}

#endif //LIBCOMMON_SRC_DATATYPES_CHARACTER_CHARACTER_HPP_
