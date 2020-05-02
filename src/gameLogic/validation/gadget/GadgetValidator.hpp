#ifndef LIBCOMMON_GADGETVALIDATOR_HPP
#define LIBCOMMON_GADGETVALIDATOR_HPP

#include "datatypes/gameplay/GadgetAction.hpp"
#include "datatypes/gameplay/State.hpp"
#include "datatypes/matchconfig/MatchConfig.hpp"

namespace spy::gameplay {

    /**
     * @brief Validation for all types of GadgetAction
     */
    class GadgetValidator {
        public:
            // Static class
            GadgetValidator() = delete;

            static bool validate(const State &s, GadgetAction a, const MatchConfig &config);

        private:
            static bool validateHairdryer(const State &s, GadgetAction a);

            static bool validateRocketPen(const State &s, GadgetAction a);

            static bool validateTechnicolourPrism(const State &s, GadgetAction a);

            static bool validatePoisonPills(const State &s, GadgetAction a);

            static bool validateLaserCompact(const State &s, GadgetAction a);

            static bool validateMoleDie(const State &s, GadgetAction a, const MatchConfig &config);

            static bool validateGasGloss(const State &s, GadgetAction a);

            static bool validateMothballPouch(const State &s, GadgetAction a, const MatchConfig &config);

            static bool validateFogTin(const State &s, GadgetAction a, const MatchConfig &config);

            static bool validateGrapple(const State &s, GadgetAction a, const MatchConfig &config);

            static bool validateJetpack(const State &s, GadgetAction a);

            static bool validateMagneticWatch(const State &s, GadgetAction a);

            static bool validateWiretapWithEarplugs(const State &s, GadgetAction a);

            static bool validateChickenFeed(const State &s, GadgetAction a);

            static bool validateNugget(const State &s, GadgetAction a);

            static bool validateMirrorOfWilderness(const State &s, GadgetAction a);

            static bool validatePocketLitter(const State &s, GadgetAction a);

            static bool validateDiamondCollar(const State &s, GadgetAction a);

            static bool validateCocktail(const State &s, GadgetAction a);

            static bool validateBowlerBlade(const State &s, GadgetAction a, const MatchConfig &config);
    };
}

#endif //LIBCOMMON_GADGETVALIDATOR_HPP
