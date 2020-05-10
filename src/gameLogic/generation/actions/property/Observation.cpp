//
// Created by Carolin on 08.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateObservation(const State &/*s*/, const util::UUID &/*activeCharacter*/) {

        // TODO implement
        return {nullptr};
    }
}