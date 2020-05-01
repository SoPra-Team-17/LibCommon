/**
 * @file GadgetExecutor.hpp
 * @author ottojo
 */

#ifndef LIBCOMMON_GADGETEXECUTOR_HPP
#define LIBCOMMON_GADGETEXECUTOR_HPP

#include <datatypes/gameplay/GadgetAction.hpp>
#include <datatypes/gameplay/State.hpp>

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
            static bool execute(State &s, GadgetAction action);

        private:
            // TODO: Gadget execution methods

            static bool executeHairDryer(State &s, const GadgetAction &action);

    };
}

#endif //LIBCOMMON_GADGETEXECUTOR_HPP
