#ifndef LIBCOMMON_GADGETVALIDATOR_HPP
#define LIBCOMMON_GADGETVALIDATOR_HPP

#include <datatypes/gameplay/GadgetAction.hpp>
#include <datatypes/gameplay/State.hpp>

namespace spy::gameplay {

    /**
     * @brief Validation for all types of GadgetAction
     */
    class GadgetValidator {
        public:
            // Static class
            GadgetValidator() = delete;

            static bool validate(const State &s, GadgetAction a);

        private:
            // TODO add gadgets
            static bool validateRocketPen(const State &s, GadgetAction a);

            static bool validateTechnicolourPrism(const State &s, GadgetAction a);

            static bool validatePoisonPills(const State &s, GadgetAction a);

            static bool validateLaserCompact(const State &s, GadgetAction a);

            static bool validateMoleDie(const State &s, GadgetAction a);
    };
}

#endif //LIBCOMMON_GADGETVALIDATOR_HPP
