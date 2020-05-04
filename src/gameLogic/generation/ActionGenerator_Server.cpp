//
// Created by Carolin on 04.05.2020.
//

#include "ActionGenerator.hpp"

namespace spy::gameplay {
    std::shared_ptr<BaseOperation>
    ActionGenerator::generateExfiltration(const State &/*s*/, const util::UUID &/*damagedCharacter*/) {
        // TODO implement
        return std::shared_ptr<BaseOperation>();
    }

    std::shared_ptr<BaseOperation> ActionGenerator::generateCatAction(const State &/*s*/) {
        // TODO implement
        return std::shared_ptr<BaseOperation>();
    }

    std::shared_ptr<BaseOperation> ActionGenerator::generateJanitorAction(const State &/*s*/) {
        // TODO implement
        return std::shared_ptr<BaseOperation>();
    }

    std::shared_ptr<BaseOperation> ActionGenerator::generateNPCAction(const State &/*s*/, const util::UUID &/*activeNPC*/) {
        // TODO implement
        return std::shared_ptr<BaseOperation>();
    }
}