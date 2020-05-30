//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    std::shared_ptr<const BaseOperation> ActionExecutor::executeRetire(State &s, const RetireAction &op) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());
        character->setActionPoints(0);
        character->setMovePoints(0);

        auto retOp = std::make_shared<RetireAction>(op);
        retOp->setSuccessful(true);

        return retOp;
    }
}