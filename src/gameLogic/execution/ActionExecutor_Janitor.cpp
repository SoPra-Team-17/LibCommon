//
// Created by jonas on 28.04.20.
//
#include <util/GameLogicUtils.hpp>
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    std::shared_ptr<const BaseOperation> ActionExecutor::executeJanitor(State &s, const JanitorAction &op) {
        s.setJanitorCoordinates(op.getTarget());
        auto character = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), op.getTarget());
        character->setCoordinates(std::nullopt);

        auto retOp = std::make_shared<JanitorAction>(op);
        retOp->setSuccessful(true);

        return retOp;
    }
}