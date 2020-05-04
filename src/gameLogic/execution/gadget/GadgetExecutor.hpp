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

            static bool executeGrapple(State &s, const GadgetAction &action, const MatchConfig &config);

            static bool executeTechnicolorPrism(State &s, const GadgetAction &a);

    };
}

#endif //LIBCOMMON_GADGETEXECUTOR_HPP
