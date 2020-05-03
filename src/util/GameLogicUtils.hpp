/**
 * @file   GameLogicUtils.hpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  definition of gadget utils
 */

#ifndef LIBCOMMON_GAMELOGICUTILS_HPP
#define LIBCOMMON_GAMELOGICUTILS_HPP

#include "datatypes/gameplay/State.hpp"

namespace spy::util {
    class GameLogicUtils {
        public:
            GameLogicUtils() = delete;

            /**
             * @brief       checks if a field contains a cocktail, or if the person standing on the field is holding one
             * @param s     current state
             * @param pt    target field which is checked
             * @return      true if there is a cocktail, false if there isn't
             */
            static bool hasCocktail(const spy::gameplay::State &s, const Point &pt);

            /**
             * @brief           checks if a character holds a certain object
             * @param s         current state
             * @param id        character id, who is checked
             * @param type      gadget for which is checked
             * @return          true if character has gadget
             */
            static bool characterHasGadget(const spy::gameplay::State &s, const UUID &id, spy::gadget::GadgetEnum type);

            /**
             * @brief           Checks if a person is at the specified location
             * @param s         current state
             * @param target    coordinate to check for a person
             * @return          true if a person is at the specified location, false otherwise
             */
            static bool isPersonOnField(const gameplay::State &s, const Point &target);

            /**
             * @brief               checks if a other person is on a neighboring field
             * @param s             current state
             * @param target        input target
             * @param charCoord     coordinates of character
             * @return              true of person is on field and field is neighboring
             */
            static bool
            personOnNeighboringField(const spy::gameplay::State &s, const Point &target, const Point &charCoord);

            /**
             * @brief       checks the bowler blade line of sight
             * @note        the implementation from FieldMap is used, with the modification, that characters also block the LoS
             * @param s     current state
             * @param p1    point 1
             * @param p2    point 2
             * @return      true if line of sight is free
             */
            static bool bowlerBladeLineOfSight(const spy::gameplay::State &s, const Point &p1, const Point &p2);

            /**
             * Searches the set for a character at the given point. Returns first match.
             * @param cs CharacterSet to search in
             * @param  p Point to search for. Has to be in the map.
             * @return Const iterator to the found character if one at the specified point exits, otherwise a
             *         const iterator to the end of the set.
             */
            static std::vector<character::Character>::const_iterator findInCharacterSetByCoordinates(const character::CharacterSet &cs, const util::Point &p);

            /**
             * Searches the set for a character at the given point. Returns first match.
             * @param cs CharacterSet to search in
             * @param  p Point to search for. Has to be in the map.
             * @return Iterator to the found character if one at the specified point exits, otherwise an
             *         iterator to the end of the set.
             */
            static std::vector<character::Character>::iterator getInCharacterSetByCoordinates(character::CharacterSet &cs, const util::Point &p);
    };
}

#endif //LIBCOMMON_GAMELOGICUTILS_HPP
