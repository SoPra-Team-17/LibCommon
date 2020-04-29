//
// Created by jonas on 28.04.20.
//

#ifndef LIBCOMMON_ACTIONEXECUTOR_HPP
#define LIBCOMMON_ACTIONEXECUTOR_HPP

#include <datatypes/gameplay/State.hpp>
#include <datatypes/gameplay/Exfiltration.hpp>
#include <datatypes/gameplay/GadgetAction.hpp>
#include <datatypes/gameplay/GambleAction.hpp>
#include <datatypes/gameplay/Movement.hpp>
#include <datatypes/gameplay/PropertyAction.hpp>

namespace spy::gameplay {
    /**
     * @brief Methods to apply a valid Operation to a State
     */
    class ActionExecutor {
        public:
            ActionExecutor() = delete;

            static bool execute(State &s, const std::shared_ptr<Operation>& op);

        private:
            /**
             * Execute Operation (CAT_ACTION, JANITOR_ACTION, RETIRE, SPY_ACTION)
             * @param op Operation to execute, has to be valid
             * @return true, if Operation was successful
             */
            static bool execute(State &s, const Operation &op);

            /**
             * Execute Exfiltration
             * @param op Operation to execute, has to be valid
             * @return true, if Exfiltration was successful
             */
            static bool execute(State &s, const Exfiltration &op);

            /**
             * Execute GadgetAction
             * @param op Operation to execute, has to be valid
             * @return true, if GadgetAction was successful
             */
            static bool execute(State &s, const GadgetAction &op);

            /**
             * Execute GambleAction
             * @param op Operation to execute, has to be valid
             * @return true, if GambleAction was successful
             */
            static bool execute(State &s, const GambleAction &op);

            /**
             * Execute Movement
             * @param op Operation to execute, has to be valid
             * @return true, if Movement was successful
             */
            static bool execute(State &s, const Movement &op);

            /**
             * Execute PropertyAction
             * @param op Operation to execute, has to be valid
             * @return true, if PropertyAction was successful
             */
            static bool execute(State &s, const PropertyAction &op);
    };
}

#endif //LIBCOMMON_ACTIONEXECUTOR_HPP
