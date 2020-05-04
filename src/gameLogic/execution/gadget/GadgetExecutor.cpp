//
// Created by jonas on 28.04.20.
//

#include "GadgetExecutor.hpp"

namespace spy::gameplay {
    bool GadgetExecutor::execute(State &s, GadgetAction action, const MatchConfig &config) {
        // TODO: implement
        switch (action.getGadget()) {
            case gadget::GadgetEnum::HAIRDRYER:
                return executeHairDryer(s, action);
            case gadget::GadgetEnum::MOLEDIE:
                break;
            case gadget::GadgetEnum::TECHNICOLOUR_PRISM:
                break;
            case gadget::GadgetEnum::BOWLER_BLADE:
                break;
            case gadget::GadgetEnum::MAGNETIC_WATCH:
                break;
            case gadget::GadgetEnum::POISON_PILLS:
                break;
            case gadget::GadgetEnum::LASER_COMPACT:
                break;
            case gadget::GadgetEnum::ROCKET_PEN:
                break;
            case gadget::GadgetEnum::GAS_GLOSS:
                return executeGasGloss(s, action, config);
            case gadget::GadgetEnum::MOTHBALL_POUCH:
                break;
            case gadget::GadgetEnum::FOG_TIN:
                break;
            case gadget::GadgetEnum::GRAPPLE:
                return executeGrapple(s, action, config);
            case gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS:
                break;
            case gadget::GadgetEnum::DIAMOND_COLLAR:
                break;
            case gadget::GadgetEnum::JETPACK:
                break;
            case gadget::GadgetEnum::CHICKEN_FEED:
                break;
            case gadget::GadgetEnum::NUGGET:
                break;
            case gadget::GadgetEnum::MIRROR_OF_WILDERNESS:
                break;
            case gadget::GadgetEnum::POCKET_LITTER:
                break;
            case gadget::GadgetEnum::COCKTAIL:
                break;
            case gadget::GadgetEnum::INVALID:
                [[fallthrough]];
            default:
                throw std::invalid_argument("Execution of gadget type not implemented");
        }
        return false;
    }
}