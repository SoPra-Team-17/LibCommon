//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    bool ActionExecutor::executeSpy(State &s, const SpyAction &op, const MatchConfig &/*config*/) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());
        character->subActionPoint();
        // TODO: implement
        return false;
    }
}