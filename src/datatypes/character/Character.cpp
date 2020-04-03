//
// Created by Carolin on 02.04.2020.
//

#include "Character.hpp"

namespace spy::character {

    const spy::util::UUID &spy::character::Character::getCharacterId() const {
        return characterId;
    }

    const std::string &spy::character::Character::getName() const {
        return name;
    }

    const spy::util::Point &spy::character::Character::getCoordinates() const {
        return coordinates;
    }

    void spy::character::Character::setCoordinates(const spy::util::Point &coordinate) {
        Character::coordinates = coordinate;
    }

    int spy::character::Character::getMp() const {
        return mp;
    }

    void spy::character::Character::setMp(int mpoints) {
        Character::mp = mpoints;
    }

    int spy::character::Character::getAp() const {
        return ap;
    }

    void spy::character::Character::setAp(int apoints) {
        Character::ap = apoints;
    }

    int spy::character::Character::getHp() const {
        return hp;
    }

    void spy::character::Character::setHp(int hpoints) {
        Character::hp = hpoints;
    }

    int spy::character::Character::getIp() const {
        return ip;
    }

    void spy::character::Character::setIp(int ipoints) {
        Character::ip = ipoints;
    }

    int spy::character::Character::getChips() const {
        return chips;
    }

    void spy::character::Character::setChips(int chip) {
        Character::chips = chip;
    }

    const std::list<spy::character::PropertyEnum> &spy::character::Character::getProperties() const {
        return properties;
    }

    void spy::character::Character::setProperties(const std::list<spy::character::PropertyEnum> &propertylist) {
        Character::properties = propertylist;
    }

    const std::list<spy::gadget::Gadget> &spy::character::Character::getGadgets() const {
        return gadgets;
    }

    void spy::character::Character::setGadgets(const std::list<spy::gadget::Gadget> &gadgetlist) {
        Character::gadgets = gadgetlist;
    }

}  // namespace spy::character
