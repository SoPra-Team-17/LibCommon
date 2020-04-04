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
            /**
             * Constructor, creates a new character with the given id and name.
             * @param characterId
             * @param name
             */
            Character(util::UUID &characterId,
                      std::string &name);

            /**
             * Getter for the character Id.
             * @return Id of the character.
             */
            [[nodiscard]] const util::UUID &getCharacterId() const;

            /**
             * Getter for the character name.
             * @return Character name.
             */
            [[nodiscard]] const std::string &getName() const;

            /**
             * Getter for the current position of the character.
             * @return Character position.
             */
            [[nodiscard]] const util::Point &getCoordinates() const;

            /**
             * Setter for the position of the character.
             * @param coordinates New coordinate of the character.
             */
            void setCoordinates(const util::Point &coordinates);

            /**
             * Getter for the move points of the character.
             * @return Move points of the character.
             */
            [[nodiscard]] unsigned int getMp() const;

            /**
             * Setter for the move points of the character.
             * @param mp Move points to set.
             */
            void setMp(unsigned int mp);

            /**
             * Getter for the action points of the character.
             * @return Current action points of the character.
             */
            [[nodiscard]] unsigned int getAp() const;

            /**
             * Setter for the action points of the character.
             * @param ap Action points to set.
             */
            void setAp(unsigned int ap);

            /**
             * Getter for the health points of the character.
             * @return Current health points of the character.
             */
            [[nodiscard]] unsigned int getHp() const;

            /**
             * Setter for the health points of the character.
             * @param hp Health points to set.
             */
            void setHp(unsigned int hp);

            /**
             * Getter for the intelligence points of the character.
             * @return Current intelligence points of the character.
             */
            [[nodiscard]] unsigned int getIp() const;

            /**
             * Setter for the intelligence points of the character.
             * @param ip Intelligence points to set.
             */
            void setIp(unsigned int ip);

            /**
             * Getter for the number of gambling chips owned by the character.
             * @return Current number of gambling chips.
             */
            [[nodiscard]] unsigned int getChips() const;

            /**
             * Setter for the number of gambling chips owned by the character.
             * @param chips Chip number to set.
             */
            void setChips(unsigned int chips);

            /**
             * Getter for the character properties.
             * @return List of the character properties.
             */
            [[nodiscard]] const std::list<PropertyEnum> &getProperties() const;

            /**
             * Setter for the character properties.
             * @param properties List with the character properties that should be set.
             */
            void setProperties(const std::list<PropertyEnum> &properties);

            /**
             * Getter for the gadgets owned by the character.
             * @return List with the current gadgets of the character.
             */
            [[nodiscard]] const std::list<gadget::Gadget> &getGadgets() const;

            /**
             * Setter for the gadgets of the character.
             * @param gadgets List of gadgets to set.
             */
            void setGadgets(const std::list<gadget::Gadget> &gadgets);

        private:
            const spy::util::UUID characterId;
            const std::string name;                                     ///< Character name.
            spy::util::Point coordinates;                               ///< Current coordinate of the character.
            unsigned int mp;                                            ///< MovePoints.
            unsigned int ap;                                            ///< ActionsPoints.
            unsigned int hp;                                            ///< HealthPoints.
            unsigned int ip;                                            ///< IntelligencePoints.
            unsigned int chips;                                         ///< Number of gambling chips.
            std::list<PropertyEnum> properties;                         ///< Character properties.
            std::list<spy::gadget::Gadget> gadgets;                     ///< Gadgets owned by the character.
    };
}

#endif //LIBCOMMON_CHARACTER_HPP