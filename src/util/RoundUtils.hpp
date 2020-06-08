/**
* @file   RoundUtils.hpp
* @author Dominik Authaler
* @date   04.05.2020 (creation)
* @brief  Declaration of utility methods for round initialization.
*/

#ifndef LIBCOMMON_ROUND_UTILS_HPP
#define LIBCOMMON_ROUND_UTILS_HPP

#include "datatypes/gameplay/State.hpp"
#include "datatypes/matchconfig/MatchConfig.hpp"
#include "datatypes/statistics/VictoryEnum.hpp"

namespace spy::util {
    using VictoryInfo = std::pair<spy::character::FactionEnum, spy::statistics::VictoryEnum>;

    class RoundUtils {
        public:
            RoundUtils() = delete;

            /**
             * Places a cocktail on all empty bar tables.
             * @param s Current state that should be modified.
             */
            static void refillBarTables(spy::gameplay::State &s);

            /**
             * Updates the fog state of each field.
             * @param s Current state that should be modified.
             */
            static void updateFog(spy::gameplay::State &s);

            /**
             * Tests for all gadgets that are applied over multiple rounds if they will end execution this round and
             * removes them if necessary.
             * @param s Current state that should be modified.
             */
            static void checkGadgetFailure(spy::gameplay::State &s, const MatchConfig &config);

            /**
             * Resets the updated flag for all fields of the map.
             * @param s Current state that should be modified.
             */
            static void resetUpdatedMarker(spy::gameplay::State &s);

            /**
             * @brief checks if game is over
             * @param s Current State, that is checked
             * @return true, if game is over
             */
            static bool isGameOver(const spy::gameplay::State &s);

            /**
             * @brief updates state, when game is over
             * @param s CurrentState that should be modified
             */
            static void updateGameOver(spy::gameplay::State &s, const spy::MatchConfig &config);

            /**
             * @brief determines winning faction and the reason of the victory
             * @param s Current state
             * @return faction + reason of the victory
             */
            static VictoryInfo determineWinningFaction(const spy::gameplay::State &s);

            /**
             * @brief determines action and movement points for a character
             * @param character to determine mp, ap
             */
            static void determinePoints(spy::character::Character &character);
    };
}

#endif //LIBCOMMON_ROUND_UTILS_HPP
