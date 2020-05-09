//
// Created by Carolin on 07.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateAllPropertyActions(const State &s, const util::UUID &activeCharacter, const MatchConfig &/*config*/) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generatePropertyActions(const State &s, const util::UUID &activeCharacter, character::PropertyEnum /*property*/) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement: switch property
        return {nullptr};
    }
}
