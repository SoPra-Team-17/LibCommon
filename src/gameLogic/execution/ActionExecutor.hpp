/**
* @file   ActionExecutor.hpp
* @author Jonas
* @date   28.04.2020 (creation)
* @brief  Definition of the static action execution class.
*/

#ifndef LIBCOMMON_ACTIONEXECUTOR_HPP
#define LIBCOMMON_ACTIONEXECUTOR_HPP

#include "datatypes/gameplay/State.hpp"
#include "datatypes/gameplay/CatAction.hpp"
#include "datatypes/gameplay/Exfiltration.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"
#include "datatypes/gameplay/GambleAction.hpp"
#include "datatypes/gameplay/JanitorAction.hpp"
#include "datatypes/gameplay/Movement.hpp"
#include "datatypes/gameplay/PropertyAction.hpp"
#include "datatypes/gameplay/RetireAction.hpp"
#include "datatypes/gameplay/SpyAction.hpp"
#include "datatypes/matchconfig/MatchConfig.hpp"

namespace spy::gameplay {
    /**
     * @brief Methods to apply a valid Operation to a State
     */
    class ActionExecutor {
        public:
            ActionExecutor() = delete;

            static std::shared_ptr<const BaseOperation>
            execute(State &s, std::shared_ptr<const BaseOperation> op, const MatchConfig &config);

        private:

            /**
             * Execute Exfiltration
             * @param op Operation to execute, has to be valid
             * @return resulting operation with success parameter set
             */
            static std::shared_ptr<const BaseOperation> executeExfiltration(State &s, const Exfiltration &op);

            /**
             * Execute GadgetAction
             * @param op Operation to execute, has to be valid
             * @return resulting operation with success parameter set
             */
            static std::shared_ptr<const BaseOperation>
            executeGadget(State &s, const GadgetAction &op, const MatchConfig &config);

            /**
             * Execute GambleAction
             * @param op Operation to execute, has to be valid
             * @return resulting operation with success parameter set
             */
            static std::shared_ptr<const BaseOperation> executeGamble(State &s, const GambleAction &op);

            /**
             * Execute Movement
             * @param op Operation to execute, has to be valid
             * @return resulting operation with success parameter set
             */
            static std::shared_ptr<const BaseOperation> executeMovement(State &s, const Movement &op);

            /**
             * Execute PropertyAction
             * @param op Operation to execute, has to be valid
             * @return resulting operation with success parameter set
             */
            static std::shared_ptr<const BaseOperation>
            executeProperty(State &s, const PropertyAction &op, const MatchConfig &config);

            /**
             * Execute SpyAction
             * @param op Operation to execute, has to be valid
             * @return resulting operation with success parameter set
             */
            static std::shared_ptr<const BaseOperation>
            executeSpy(State &s, const SpyAction &op, const MatchConfig &config);

            /**
             * Execute CatAction
             * @param op Operation to execute, has to be valid
             * @return resulting operation with success parameter set
             */
            static std::shared_ptr<const BaseOperation> executeCat(State &s, const CatAction &op);

            /**
             * Execute JanitorAction
             * @param op Operation to execute, has to be valid
             * @return resulting operation with success parameter set
             */
            static std::shared_ptr<const BaseOperation> executeJanitor(State &s, const JanitorAction &op);

            /**
             * Execute RetireAction
             * @param op Operation to execute, has to be valid
             * @return resulting operation with success parameter set
             */
            static std::shared_ptr<const BaseOperation> executeRetire(State &s, const RetireAction &op);
    };
}

#endif //LIBCOMMON_ACTIONEXECUTOR_HPP
