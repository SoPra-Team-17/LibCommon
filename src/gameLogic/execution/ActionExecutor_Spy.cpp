//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    std::shared_ptr<const BaseOperation>
    ActionExecutor::executeSpy(State &s, const SpyAction &op, const MatchConfig &/*config*/) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());
        character->subActionPoint();
        // TODO: implement

        auto retOp = std::make_shared<SpyAction>(op);
        retOp->setSuccessful(false);

        return retOp;
    }
}