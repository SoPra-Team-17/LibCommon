//
// Created by Carolin on 07.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generatePropertyActions(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateObservation(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateBangAndBurn(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }
}
