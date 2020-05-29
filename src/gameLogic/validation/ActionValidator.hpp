/**
* @file   ActionValidator.hpp
* @author Jonas
* @date   28.04.2020 (creation)
* @brief  Definition of the static action validation class.
*/

#ifndef LIBCOMMON_ACTIONVALIDATOR_HPP
#define LIBCOMMON_ACTIONVALIDATOR_HPP


#include "datatypes/gameplay/State.hpp"
#include "datatypes/gameplay/Exfiltration.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"
#include "datatypes/gameplay/GambleAction.hpp"
#include "datatypes/gameplay/Movement.hpp"
#include "datatypes/gameplay/PropertyAction.hpp"
#include "datatypes/gameplay/SpyAction.hpp"
#include "datatypes/gameplay/CatAction.hpp"
#include "datatypes/gameplay/JanitorAction.hpp"
#include "datatypes/gameplay/RetireAction.hpp"
#include "datatypes/matchconfig/MatchConfig.hpp"

namespace spy::gameplay {
    /**
     * @brief validate() functions for all possible Operations
     */
    class ActionValidator {
        public:
            // Static class
            ActionValidator() = delete;

            static bool validate(const State &s, std::shared_ptr<const BaseOperation> op, const MatchConfig &config);

            static bool validateGadgetAction(const State &s, GadgetAction op, const MatchConfig &config);

            static bool validateGambleAction(const State &s, const GambleAction& op);

            static bool validateMovement(const State &s, Movement op);

            static bool validatePropertyAction(const State &s, const PropertyAction& op);

            static bool validateSpyAction(const State &s, const SpyAction& op);

            static bool validateRetireAction(const State &s, const RetireAction& op);

    };
}

#endif //LIBCOMMON_ACTIONVALIDATOR_HPP
