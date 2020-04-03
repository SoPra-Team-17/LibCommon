//
// Created by Carolin on 02.04.2020.
//

#include "Character.hpp"

namespace spy::character {

    const util::UUID &Character::getCharacterId() const {
        return characterId;
    }

    const std::string &Character::getName() const {
        return name;
    }

    const util::Point &Character::getCoordinates() const {
        return coordinates;
    }

    void Character::setCoordinates(const util::Point &coordinate) {
        Character::coordinates = coordinate;
    }

    int Character::getMp() const {
        return mp;
    }

    void Character::setMp(int mpoints) {
        Character::mp = mpoints;
    }

    int Character::getAp() const {
        return ap;
    }

    void Character::setAp(int apoints) {
        Character::ap = apoints;
    }

    int Character::getHp() const {
        return hp;
    }

    void Character::setHp(int hpoints) {
        Character::hp = hpoints;
    }

    int Character::getIp() const {
        return ip;
    }

    void Character::setIp(int ipoints) {
        Character::ip = ipoints;
    }

    int Character::getChips() const {
        return chips;
    }

    void Character::setChips(int chip) {
        Character::chips = chip;
    }

    const std::list<PropertyEnum> &Character::getProperties() const {
        return properties;
    }

    void Character::setProperties(const std::list<PropertyEnum> &propertylist) {
        Character::properties = propertylist;
    }

    const std::list<gadget::Gadget> &Character::getGadgets() const {
        return gadgets;
    }

    void Character::setGadgets(const std::list<gadget::Gadget> &gadgetlist) {
        Character::gadgets = gadgetlist;
    }

}  // namespace spy::character
