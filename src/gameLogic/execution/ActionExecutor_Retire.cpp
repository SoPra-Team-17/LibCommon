//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    bool ActionExecutor::executeRetire(State &s, const RetireAction &op) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());
        character->setActionPoints(0);
        character->setMovePoints(0);
        return true;
    }
}