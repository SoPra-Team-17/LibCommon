/**
 * @file GadgetExecutor.hpp
 * @author ottojo
 */

#ifndef LIBCOMMON_GADGETEXECUTOR_HPP
#define LIBCOMMON_GADGETEXECUTOR_HPP

#include "datatypes/gameplay/GadgetAction.hpp"
#include "datatypes/gameplay/State.hpp"
#include "datatypes/matchconfig/MatchConfig.hpp"

namespace spy::gameplay {

    /**
     * @brief Methods to apply GadgetActions to State
     */
    class GadgetExecutor {
        public:
            GadgetExecutor() = delete;

            /**
             * @param action Operation to execute, has to be valid
             */
            static bool execute(State &s, GadgetAction action, const MatchConfig &config);

        private:
            // TODO: Gadget execution methods

            static bool executeHairDryer(State &s, const GadgetAction &action);

            static bool executeTechnicolorPrism(State &s, const GadgetAction &a);

            static bool executeBowlerBlade(State &s, const GadgetAction &a, const MatchConfig &config);

            static bool executeChickenFeed(State &s, const GadgetAction &a);

            static bool executeMirrorOfWilderness(State &s, const GadgetAction &a, const MatchConfig &config);

            static bool executeNugget(State &s, const GadgetAction &a);

            static bool executeRocketPen(State &s, const GadgetAction &a, const MatchConfig &config);

            static bool executeMoleDie(State &s, const GadgetAction &a);

    };
}

#endif //LIBCOMMON_GADGETEXECUTOR_HPP
