//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    bool ActionExecutor::executeProperty(State &s, const PropertyAction &op, const MatchConfig &/*config*/) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());
        character->subActionPoint();
        // TODO: implement
        return false;
    }
}