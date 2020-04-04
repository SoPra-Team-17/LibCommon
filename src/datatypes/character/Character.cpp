/**
 * @file   Character.cpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Definition of the character class.
 */

#include "Character.hpp"

namespace spy::character {

    Character::Character(util::UUID &characterId, std::string &name) : characterId(characterId),
                                                                       name(name),
                                                                       coordinates{spy::util::Point{}},
                                                                       mp(0),
                                                                       ap(0),
                                                                       hp(100),
                                                                       ip(0),
                                                                       chips(10),
                                                                       properties({}),
                                                                       gadgets({}) {

    }

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

    unsigned int Character::getMp() const {
        return mp;
    }

    void Character::setMp(unsigned int mPoints) {
        Character::mp = mPoints;
    }

    unsigned int Character::getAp() const {
        return ap;
    }

    void Character::setAp(unsigned int aPoints) {
        Character::ap = aPoints;
    }

    unsigned int Character::getHp() const {
        return hp;
    }

    void Character::setHp(unsigned int hPoints) {
        Character::hp = hPoints;
    }

    unsigned int Character::getIp() const {
        return ip;
    }

    void Character::setIp(unsigned int iPoints) {
        Character::ip = iPoints;
    }

    unsigned int Character::getChips() const {
        return chips;
    }

    void Character::setChips(unsigned int chip) {
        Character::chips = chip;
    }

    const std::list<PropertyEnum> &Character::getProperties() const {
        return properties;
    }

    void Character::setProperties(const std::list<PropertyEnum> &propertyList) {
        Character::properties = propertyList;
    }

    const std::list<gadget::Gadget> &Character::getGadgets() const {
        return gadgets;
    }

    void Character::setGadgets(const std::list<gadget::Gadget> &gadgetList) {
        Character::gadgets = gadgetList;
    }

}  // namespace spy::character
