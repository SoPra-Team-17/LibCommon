/**
 * @file   GadgetValidator.cpp
 * @author Jonas
 * @date   28.04.2020 (creation)
 * @brief  Validator class for the Gadget action.
 */

#include "GadgetValidator.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validate(const State &s, GadgetAction op) {
        using gadget::GadgetEnum;
        // TODO implement
        switch (op.getGadget()) {
            case GadgetEnum::ROCKET_PEN:
                return GadgetValidator::validateRocketPen(s, op);

            case GadgetEnum::HAIRDRYER:
                return GadgetValidator::validateHairdryer(s, op);

            case GadgetEnum::GAS_GLOSS:
                return GadgetValidator::validateGasGloss(s, op);

            case GadgetEnum::FOG_TIN:
                return GadgetValidator::validateFogTin(s, op);

            case GadgetEnum::CHICKEN_FEED:
                return GadgetValidator::validateChickenFeed(s, op);

            case GadgetEnum::BOWLER_BLADE:
                return GadgetValidator::validateBowlerBlade(s, op);

            case GadgetEnum::MOLEDIE:
                return GadgetValidator::validateMoleDie(s, op);

            case GadgetEnum::TECHNICOLOUR_PRISM:
                return GadgetValidator::validateTechnicolourPrism(s, op);

            case GadgetEnum::MAGNETIC_WATCH:
                return GadgetValidator::validateMagneticWatch(s, op);

            case GadgetEnum::POISON_PILLS:
                return GadgetValidator::validatePoisonPills(s, op);

            case GadgetEnum::LASER_COMPACT:
                return GadgetValidator::validateLaserCompact(s, op);

            case GadgetEnum::MOTHBALL_POUCH:
                return GadgetValidator::validateMothballPouch(s, op);

            case GadgetEnum::GRAPPLE:
                return GadgetValidator::validateGrapple(s, op);

            case GadgetEnum::WIRETAP_WITH_EARPLUGS:
                return GadgetValidator::validateWiretapWithEarplugs(s, op);

            case GadgetEnum::DIAMOND_COLLAR:
                return GadgetValidator::validateDiamondCollar(s, op);

            case GadgetEnum::JETPACK:
                return GadgetValidator::validateJetpack(s, op);

            case GadgetEnum::NUGGET:
                return GadgetValidator::validateNugget(s, op);

            case GadgetEnum::MIRROR_OF_WILDERNESS:
                return GadgetValidator::validateMirrorOfWilderness(s, op);

            case GadgetEnum::POCKET_LITTER:
                return GadgetValidator::validatePocketLitter(s, op);

            case GadgetEnum::COCKTAIL:
                return GadgetValidator::validateCocktail(s, op);

            default:
                return false;
        }
    }
}