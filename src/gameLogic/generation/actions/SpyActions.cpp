//
// Created by Carolin on 07.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateSpyActions(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);

        // TODO implement
        return {nullptr};
    }
}
