//
// Created by Carolin on 07.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateAllGadgetActions(const State &s, const util::UUID &activeCharacter, const MatchConfig &config) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        std::vector<std::shared_ptr<BaseOperation>> actions;
        for (const auto &g: character->getGadgets()) {
            auto a = generateGadgetActions(s, activeCharacter, g->getType(), config);
            actions.insert(actions.end(), a.begin(), a.end());
        }

        return actions;
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateGadgetActions(const State &s, const util::UUID &activeCharacter,
                                           gadget::GadgetEnum gadget, const spy::MatchConfig &config) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        switch (gadget) {
            case gadget::GadgetEnum::HAIRDRYER:
                return generateHairDryer(s, activeCharacter, config);
            case gadget::GadgetEnum::MOLEDIE:
                return generateMoleDie(s, activeCharacter, config);
            case gadget::GadgetEnum::TECHNICOLOUR_PRISM:
                return generateTechnicolorPrism(s, activeCharacter, config);
            case gadget::GadgetEnum::BOWLER_BLADE:
                return generateBowlerBlade(s, activeCharacter, config);
            case gadget::GadgetEnum::POISON_PILLS:
                return generatePoisonPills(s, activeCharacter, config);
            case gadget::GadgetEnum::LASER_COMPACT:
                return generateLaserCompact(s, activeCharacter, config);
            case gadget::GadgetEnum::ROCKET_PEN:
                return generateRocketPen(s, activeCharacter, config);
            case gadget::GadgetEnum::GAS_GLOSS:
                return generateGasGloss(s, activeCharacter, config);
            case gadget::GadgetEnum::MOTHBALL_POUCH:
                return generateMothballPouch(s, activeCharacter, config);
            case gadget::GadgetEnum::FOG_TIN:
                return generateFogTin(s, activeCharacter, config);
            case gadget::GadgetEnum::GRAPPLE:
                return generateGrapple(s, activeCharacter, config);
            case gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS:
                return generateWiretapWithEarplugs(s, activeCharacter, config);
            case gadget::GadgetEnum::DIAMOND_COLLAR:
                return generateDiamondCollar(s, activeCharacter, config);
            case gadget::GadgetEnum::JETPACK:
                return generateJetpack(s, activeCharacter, config);
            case gadget::GadgetEnum::CHICKEN_FEED:
                return generateChickenFeed(s, activeCharacter, config);
            case gadget::GadgetEnum::NUGGET:
                return generateNugget(s, activeCharacter, config);
            case gadget::GadgetEnum::MIRROR_OF_WILDERNESS:
                return generateMirrorOfWilderness(s, activeCharacter, config);
            case gadget::GadgetEnum::COCKTAIL:
                return generateCocktail(s, activeCharacter, config);
            case gadget::GadgetEnum::ANTI_PLAGUE_MASK:
                [[fallthrough]];
            case gadget::GadgetEnum::POCKET_LITTER:
                [[fallthrough]];
            case gadget::GadgetEnum::MAGNETIC_WATCH:
                [[fallthrough]];
            case gadget::GadgetEnum::INVALID:
                [[fallthrough]];
            default:
                return {};
        }
    }
}
