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
     * @brief Methods to apply an Operation to a State
     */
    class ActionExecutor {
        public:
            ActionExecutor() = delete;

            /**
             * Execute Exfiltration
             * @return true, if Exfiltration was successful
             */
            static bool execute(State &s, Exfiltration op);

            /**
            * Execute GadgetAction
            * @return true, if GadgetAction was successful
            */
            static bool execute(State &s, GadgetAction op);

            /**
            * Execute GambleAction
            * @return true, if GambleAction was successful
            */
            static bool execute(State &s, GambleAction op);

            /**
            * Execute Movement
            * @return true, if Movement was successful
            */
            static bool execute(State &s, Movement op);

            /**
            * Execute PropertyAction
            * @return true, if PropertyAction was successful
            */
            static bool execute(State &s, PropertyAction op);
    };
}

#endif //LIBCOMMON_ACTIONEXECUTOR_HPP
