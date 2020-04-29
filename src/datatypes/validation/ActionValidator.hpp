
#ifndef LIBCOMMON_ACTIONVALIDATOR_HPP
#define LIBCOMMON_ACTIONVALIDATOR_HPP


#include <datatypes/gameplay/State.hpp>
#include <datatypes/gameplay/Exfiltration.hpp>
#include <datatypes/gameplay/GadgetAction.hpp>
#include <datatypes/gameplay/GambleAction.hpp>
#include <datatypes/gameplay/Movement.hpp>
#include <datatypes/gameplay/PropertyAction.hpp>

namespace spy::gameplay {
    /**
     * @brief validate() functions for all possible Operations
     */
    class ActionValidator {
        public:
            // Static class
            ActionValidator() = delete;

            static bool validate(const State &s, const std::shared_ptr<Operation>& op);

        private:

            static bool validate(const State &s, Operation op);

            static bool validate(const State &s, Exfiltration op);

            static bool validate(const State &s, GadgetAction op);

            static bool validate(const State &s, GambleAction op);

            static bool validate(const State &s, Movement op);

            static bool validate(const State &s, PropertyAction op);

    };
}

#endif //LIBCOMMON_ACTIONVALIDATOR_HPP
