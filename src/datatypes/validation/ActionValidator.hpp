
#ifndef LIBCOMMON_ACTIONVALIDATOR_HPP
#define LIBCOMMON_ACTIONVALIDATOR_HPP


#include <datatypes/gameplay/State.hpp>
#include <datatypes/gameplay/Exfiltration.hpp>
#include <datatypes/gameplay/GadgetAction.hpp>
#include <datatypes/gameplay/GambleAction.hpp>
#include <datatypes/gameplay/Movement.hpp>
#include <datatypes/gameplay/PropertyAction.hpp>
#include <datatypes/gameplay/SpyAction.hpp>
#include <datatypes/gameplay/CatAction.hpp>
#include <datatypes/gameplay/JanitorAction.hpp>
#include <datatypes/gameplay/RetireAction.hpp>

namespace spy::gameplay {
    /**
     * @brief validate() functions for all possible Operations
     */
    class ActionValidator {
        public:
            // Static class
            ActionValidator() = delete;

            static bool validate(const State &s, std::shared_ptr<const BaseOperation> op);

        private:

            static bool validateExfiltration(const State &s, Exfiltration op);

            static bool validateGadgetAction(const State &s, GadgetAction op);

            static bool validateGambleAction(const State &s, GambleAction op);

            static bool validateMovement(const State &s, Movement op);

            static bool validatePropertyAction(const State &s, PropertyAction op);

            static bool validateSpyAction(const State &s, SpyAction op);

            static bool validateCatAction(const State &s, CatAction op);

            static bool validateJanitorAction(const State &s, JanitorAction op);

            static bool validateRetireAction(const State &s, RetireAction op);

    };
}

#endif //LIBCOMMON_ACTIONVALIDATOR_HPP
