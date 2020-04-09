/**
 * @file   Character.cpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Definition of the character class.
 */

#include "Character.hpp"

namespace spy::character {

    Character::Character(const util::UUID &characterId, const std::string &name) : characterId(characterId),
                                                                                   name(name) {}

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

    unsigned int Character::getMovePoints() const {
        return movePoints;
    }

    void Character::setMovePoints(unsigned int mp) {
        Character::movePoints = mp;
    }

    unsigned int Character::getActionPoints() const {
        return actionPoints;
    }

    void Character::setActionPoints(unsigned int ap) {
        Character::actionPoints = ap;
    }

    unsigned int Character::getHealthPoints() const {
        return healthPoints;
    }

    void Character::setHealthPoints(unsigned int hp) {
        Character::healthPoints = hp;
    }

    unsigned int Character::getIntelligencePoints() const {
        return intelligencePoints;
    }

    void Character::setIntelligencePoints(unsigned int ip) {
        Character::intelligencePoints = ip;
    }

    unsigned int Character::getChips() const {
        return chips;
    }

    void Character::setChips(unsigned int chip) {
        Character::chips = chip;
    }

    const std::vector<PropertyEnum> &Character::getProperties() const {
        return properties;
    }

    void Character::setProperties(const std::vector<PropertyEnum> &propertyList) {
        Character::properties = propertyList;
    }

    const std::vector<gadget::Gadget> &Character::getGadgets() const {
        return gadgets;
    }

    void Character::setGadgets(const std::vector<gadget::Gadget> &gadgetList) {
        Character::gadgets = gadgetList;
    }

    void to_json(nlohmann::json &j, const spy::character::Character &c) {
        j["characterId"] = c.characterId;
        j["name"] = c.name;
        j["coordinates"] = c.coordinates;
        j["mp"] = c.movePoints;
        j["ap"] = c.actionPoints;
        j["hp"] = c.healthPoints;
        j["ip"] = c.intelligencePoints;
        j["chips"] = c.chips;
        j["properties"] = c.properties;
        j["gadgets"] = c.gadgets;
    }

    void from_json(const nlohmann::json &j, spy::character::Character &c) {
        j.at("characterId").get_to(c.characterId);
        j.at("name").get_to(c.name);
        j.at("coordinates").get_to(c.coordinates);
        j.at("mp").get_to(c.movePoints);
        j.at("ap").get_to(c.actionPoints);
        j.at("hp").get_to(c.healthPoints);
        j.at("ip").get_to(c.intelligencePoints);
        j.at("chips").get_to(c.chips);
        j.at("properties").get_to(c.properties);
        j.at("gadgets").get_to(c.gadgets);
    }

}  // namespace spy::character
