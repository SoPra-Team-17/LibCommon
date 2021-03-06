/**
 * @file   Character.cpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Definition of the character class.
 */

#include "Character.hpp"
#include "util/GadgetSerialization.hpp"

namespace spy::character {

    Character::Character(const util::UUID &characterId, const std::string &name) : characterId(characterId),
                                                                                   name(name) {}

    const util::UUID &Character::getCharacterId() const {
        return characterId;
    }

    const std::string &Character::getName() const {
        return name;
    }

    const std::optional<util::Point> &Character::getCoordinates() const {
        return coordinates;
    }

    void Character::setCoordinates(const std::optional<util::Point> &coordinate) {
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

    int Character::getHealthPoints() const {
        return healthPoints;
    }

    void Character::setHealthPoints(int hp) {
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

    const std::set<PropertyEnum> &Character::getProperties() const {
        return properties;
    }

    std::set<PropertyEnum> &Character::getProperties() {
        return properties;
    }

    void Character::setProperties(const std::set<PropertyEnum> &propertyList) {
        Character::properties = propertyList;
    }

    const std::vector<std::shared_ptr<gadget::Gadget>> &Character::getGadgets() const {
        return gadgets;
    }

    void Character::setGadgets(const std::vector<std::shared_ptr<gadget::Gadget>> &gadgetList) {
        Character::gadgets = gadgetList;
    }

    void Character::addGadget(std::shared_ptr<gadget::Gadget> gadget) {
        Character::gadgets.push_back(std::move(gadget));
    }

    std::optional<std::shared_ptr<spy::gadget::Gadget>> Character::getGadget(spy::gadget::GadgetEnum type) {
        auto it = std::find_if(gadgets.begin(), gadgets.end(),
                            [&type](const std::shared_ptr<spy::gadget::Gadget> &g) {
                                return g->getType() == type;
                            });
        if (it != gadgets.end()) {
            return *it;
        } else {
            // character doesn't posses the requested gadget
            return std::nullopt;
        }
    }

    std::optional<const std::shared_ptr<const spy::gadget::Gadget>>
    Character::getGadget(spy::gadget::GadgetEnum type) const {
        auto it = std::find_if(gadgets.begin(), gadgets.end(),
                               [&type](const std::shared_ptr<spy::gadget::Gadget> &g) {
                                   return g->getType() == type;
                               });
        if (it != gadgets.end()) {
            return *it;
        } else {
            // character doesn't posses the requested gadget
            return std::nullopt;
        }
    }

    void to_json(nlohmann::json &j, const spy::character::Character &c) {
        j["characterId"] = c.characterId;
        j["name"] = c.name;
        if (c.coordinates.has_value()) {
            j["coordinates"] = c.coordinates.value();
        }
        j["mp"] = c.movePoints;
        j["ap"] = c.actionPoints;
        j["hp"] = c.healthPoints;
        j["ip"] = c.intelligencePoints;
        j["chips"] = c.chips;
        j["features"] = c.properties;
        j["gadgets"] = c.gadgets;
    }

    void from_json(const nlohmann::json &j, spy::character::Character &c) {
        j.at("characterId").get_to(c.characterId);
        j.at("name").get_to(c.name);
        if (j.find("coordinates") != j.end()) {
            util::Point p;
            j.at("coordinates").get_to(p);
            c.coordinates = (p.x < 0 || p.y < 0) ? std::optional<util::Point>() : p;
        }
        j.at("mp").get_to(c.movePoints);
        j.at("ap").get_to(c.actionPoints);
        j.at("hp").get_to(c.healthPoints);
        j.at("ip").get_to(c.intelligencePoints);
        j.at("chips").get_to(c.chips);
        j.at("features").get_to(c.properties);
        j.at("gadgets").get_to(c.gadgets);
    }

    bool Character::operator==(const Character &rhs) const {
        return std::tie(characterId, name, coordinates, movePoints, actionPoints, healthPoints, intelligencePoints,
                        chips, properties, gadgets) ==
               std::tie(rhs.characterId, rhs.name, rhs.coordinates, rhs.movePoints, rhs.actionPoints, rhs.healthPoints,
                        rhs.intelligencePoints, rhs.chips, rhs.properties, rhs.gadgets);
    }

    bool Character::hasProperty(PropertyEnum property) const {
        return std::find(properties.begin(), properties.end(), property) != properties.end();
    }

    void Character::setFaction(character::FactionEnum f) {
        faction = f;
    }

    character::FactionEnum Character::getFaction() const {
        return faction;
    }

    void Character::subActionPoint() {
        actionPoints--;
    }

    void Character::subMovePoint() {
        movePoints--;
    }

    void Character::removeGadget(gadget::GadgetEnum gadget) {
        gadgets.erase(std::remove_if(gadgets.begin(), gadgets.end(), [gadget](std::shared_ptr<gadget::Gadget> g) {
            return g->getType() == gadget;
        }), gadgets.end());
    }

    bool Character::hasGadget(spy::gadget::GadgetEnum type) const {
        auto gadget = std::find_if(gadgets.begin(), gadgets.end(),
                                   [type](const std::shared_ptr<gadget::Gadget> &g) {
                                       return g->getType() == type;
                                   });

        return (gadget != gadgets.end());
    }

    void Character::addHealthPoints(unsigned int add) {
        healthPoints = std::min(healthPoints + static_cast<int>(add), 100);
    }

    void Character::subHealthPoints(unsigned int sub) {
        healthPoints -= static_cast<int>(sub);
    }

    void Character::addIntelligencePoints(int points) {
        if (points < 0 && std::abs(points) >= static_cast<int>(intelligencePoints)) {
            intelligencePoints = 0;
        } else {
            intelligencePoints += points;
        }
    }

    void Character::addProperty(PropertyEnum property) {
        properties.insert(property);
    }

}  // namespace spy::character
