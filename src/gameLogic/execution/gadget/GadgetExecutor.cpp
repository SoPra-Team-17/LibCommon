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
                return executeMoleDie(s, action);
            case gadget::GadgetEnum::TECHNICOLOUR_PRISM:
                return executeTechnicolorPrism(s, action);
            case gadget::GadgetEnum::BOWLER_BLADE:
                return executeBowlerBlade(s, action, config);
            case gadget::GadgetEnum::POISON_PILLS:
                return executePoisonPills(s, action);
            case gadget::GadgetEnum::LASER_COMPACT:
                return executeLaserCompact(s, action, config);
            case gadget::GadgetEnum::ROCKET_PEN:
                return executeRocketPen(s, action, config);
            case gadget::GadgetEnum::GAS_GLOSS:
                return executeGasGloss(s, action, config);
            case gadget::GadgetEnum::MOTHBALL_POUCH:
                return executeMothballPouch(s, action, config);
            case gadget::GadgetEnum::FOG_TIN:
                return executeFogTin(s, action);
            case gadget::GadgetEnum::GRAPPLE:
                return executeGrapple(s, action, config);
            case gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS:
                return executeWiretapWithEarplugs(s, action);
            case gadget::GadgetEnum::DIAMOND_COLLAR:
                return executeDiamondCollar(s, action);
            case gadget::GadgetEnum::JETPACK:
                return executeJetpack(s, action);
            case gadget::GadgetEnum::CHICKEN_FEED:
                return executeChickenFeed(s, action);
            case gadget::GadgetEnum::NUGGET:
                return executeNugget(s, action);
            case gadget::GadgetEnum::MIRROR_OF_WILDERNESS:
                return executeMirrorOfWilderness(s, action, config);
            case gadget::GadgetEnum::COCKTAIL:
                break;
            case gadget::GadgetEnum::POCKET_LITTER:
                [[fallthrough]];
            case gadget::GadgetEnum::MAGNETIC_WATCH:
                throw std::invalid_argument("Execution of gadget type not implemented -> gadget is passive");
            case gadget::GadgetEnum::INVALID:
                [[fallthrough]];
            default:
                throw std::invalid_argument("Execution of gadget type not implemented");
        }
        return false;
    }
}