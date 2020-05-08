//
// Created by Carolin on 07.05.2020.
//

#include <datatypes/gameplay/RetireAction.hpp>
#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::shared_ptr<BaseOperation>
    ActionGenerator::generateRetire(const util::UUID &activeCharacter) {
        return std::make_shared<RetireAction>(spy::gameplay::RetireAction(activeCharacter));
    }
}
