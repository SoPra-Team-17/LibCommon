/**
 * @file   GadgetUtils.hpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  definition of gadget utils
 */

#ifndef LIBCOMMON_GADGETUTILS_HPP
#define LIBCOMMON_GADGETUTILS_HPP

#include "datatypes/gameplay/State.hpp"

namespace spy::util {
    class GadgetUtils {
        public:
            GadgetUtils() = delete;

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
    };
}

#endif //LIBCOMMON_GADGETUTILS_HPP
