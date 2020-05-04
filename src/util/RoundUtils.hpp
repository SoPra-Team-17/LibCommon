/**
* @file   RoundUtils.hpp
* @author Dominik Authaler
* @date   04.05.2020 (creation)
* @brief  Declaration of utility methods for round initialization.
*/

#ifndef LIBCOMMON_ROUND_UTILS_HPP
#define LIBCOMMON_ROUND_UTILS_HPP

#include "datatypes/gameplay/State.hpp"

namespace spy::util {
    class RoundUtils {
        public:
            RoundUtils() = delete;

            /**
             * Places a cocktail on all empty bar tables.
             * @param s Current state that should be modified.
             */
            static void refillBarTables(spy::gameplay::State &s);

            /**
             * Generates a random order for the character indexes.
             * @param s Current state
             * @return
             */
            static std::vector<unsigned int> getRandomCharacterOrder(const spy::gameplay::State &s);

            /**
             * Updates the fog state of each field.
             * @param s Current state that should be modified.
             */
            static void updateFog(spy::gameplay::State &s);

            /**
             * Tests for all gadgets that can fall out whether this happens this round and removes them
             * if necessary.
             * @param s Current state that should be modified.
             */
            static void checkGadgetFallouts(spy::gameplay::State &s);
    };
}

#endif //LIBCOMMON_ROUND_UTILS_HPP
