/**
 * @file   Character.hpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Declaration of the character class.
 */

#ifndef LIBCOMMON_CHARACTER_HPP
#define LIBCOMMON_CHARACTER_HPP

#include <string>
#include <list>
#include <datatypes/gadgets/Gadget.hpp>
#include <datatypes/character/PropertyEnum.hpp>
#include <util/UUID.hpp>
#include <util/Point.hpp>

namespace spy::character {
    /**
     * @brief Representation of a character during the game.
     */
    class Character {
        public:
            Character(util::UUID &characterId,
                      std::string &name);


            [[nodiscard]] const util::UUID &getCharacterId() const;


            [[nodiscard]] const std::string &getName() const;


            [[nodiscard]] const util::Point &getCoordinates() const;

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

            [[nodiscard]] const std::list<PropertyEnum> &getProperties() const;

            void setProperties(const std::list<PropertyEnum> &properties);

            [[nodiscard]] const std::list<gadget::Gadget> &getGadgets() const;

            void setGadgets(const std::list<gadget::Gadget> &gadgets);

        private:
            const spy::util::UUID characterId;
            const std::string name;
            spy::util::Point coordinates;
            unsigned int movePoints;
            unsigned int actionPoints;
            unsigned int healthPoints;
            unsigned int intelligencePoints;
            unsigned int chips;
            std::list<PropertyEnum> properties;
            std::list<spy::gadget::Gadget> gadgets;
    };
}

#endif //LIBCOMMON_CHARACTER_HPP