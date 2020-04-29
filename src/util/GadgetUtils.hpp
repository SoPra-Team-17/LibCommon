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
             * @brief checks if a field contains a cocktail, or if the person standing on the field is holding one
             * @param s     current state
             * @param pt    target field which is checked
             * @return      true if there is a cocktail, false if there isn't
             */
            static bool hasCocktail(const spy::gameplay::State &s, const Point &pt);

    };
}

#endif //LIBCOMMON_GADGETUTILS_HPP
