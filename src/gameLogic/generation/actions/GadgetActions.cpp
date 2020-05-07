//
// Created by Carolin on 07.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateGadgetActions(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateMoleDie(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateBowlerBlade(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateChickenFeed(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateCocktail(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateDiamondCollar(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateFogTin(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateGasGloss(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateGrapple(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateHairDryer(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateJetpack(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateLaserCompact(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateMirrorOfWilderness(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateMothballPouch(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateNugget(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generatePoisonPills(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateRocketPen(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateTechnicolorPrism(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateWiretapWithEarplugs(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }
}
