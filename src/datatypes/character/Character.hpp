/**
 * @file   Character.hpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Declaration of the character class.
 */

#ifndef LIBCOMMON_CHARACTER_HPP
#define LIBCOMMON_CHARACTER_HPP

#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <datatypes/gadgets/Gadget.hpp>
#include <datatypes/character/PropertyEnum.hpp>
#include <util/UUID.hpp>
#include <util/Point.hpp>
#include <set>
#include "FactionEnum.hpp"

namespace spy::character {
    constexpr unsigned int DEFAULT_HEALTH_POINTS = 100;
    constexpr unsigned int DEFAULT_CHIPS = 10;
    constexpr unsigned int DEFAULT_ACTION_POINTS = 0;
    constexpr unsigned int DEFAULT_MOVE_POINTS = 0;
    constexpr unsigned int DEFAULT_INTELLIGENCE_POINTS = 0;

    /**
     * @brief Representation of a character during the game.
     */
    class Character {
        public:
            Character() = default;

            Character(const util::UUID &characterId,
                      const std::string &name);

            [[nodiscard]] const util::UUID &getCharacterId() const;

            [[nodiscard]] const std::string &getName() const;

            [[nodiscard]] const std::optional<util::Point> &getCoordinates() const;

            void setCoordinates(const util::Point &coordinates);

            [[nodiscard]] unsigned int getMovePoints() const;

            void setMovePoints(unsigned int mp);

            [[nodiscard]] unsigned int getActionPoints() const;

            void setActionPoints(unsigned int ap);

            [[nodiscard]] unsigned int getHealthPoints() const;

            void setHealthPoints(unsigned int hp);

            [[nodiscard]] unsigned int getIntelligencePoints() const;

            void setIntelligencePoints(unsigned int ip);

            [[nodiscard]] unsigned int getChips() const;

            void setChips(unsigned int chips);

            [[nodiscard]] const std::set<PropertyEnum> &getProperties() const;

            [[nodiscard]]  std::set<PropertyEnum> &getProperties();

            void setProperties(const std::set<PropertyEnum> &properties);

            [[nodiscard]] const std::vector<gadget::Gadget> &getGadgets() const;

            void setGadgets(const std::vector<gadget::Gadget> &gadgets);

            void setFaction(character::FactionEnum faction);

            [[nodiscard]] character::FactionEnum getFaction() const;

            void addGadget(gadget::Gadget gadget);

            void removeGadget(gadget::GadgetEnum gadget);

            friend void to_json(nlohmann::json &j, const Character &c);

            friend void from_json(const nlohmann::json &j, Character &c);

            bool operator==(const Character &rhs) const;

            void subActionPoint();

            void subMovePoint();

            [[nodiscard]] bool hasProperty(PropertyEnum property) const;

        private:
            spy::util::UUID characterId;
            std::string name;
            std::optional<spy::util::Point> coordinates;
            unsigned int movePoints = DEFAULT_MOVE_POINTS;
            unsigned int actionPoints = DEFAULT_ACTION_POINTS;
            unsigned int healthPoints = DEFAULT_HEALTH_POINTS;
            unsigned int intelligencePoints = DEFAULT_INTELLIGENCE_POINTS;
            unsigned int chips = DEFAULT_CHIPS;
            std::set<spy::character::PropertyEnum> properties;
            std::vector<spy::gadget::Gadget> gadgets;
            character::FactionEnum faction = FactionEnum::INVALID;
    };
}

#endif //LIBCOMMON_CHARACTER_HPP
