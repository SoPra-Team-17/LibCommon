//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"
#include "gameLogic/execution/property/PropertyExecutor.hpp"

namespace spy::gameplay {
    std::shared_ptr<const BaseOperation> ActionExecutor::executeProperty(State &s, const PropertyAction &op, const MatchConfig &config) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());
        character->subActionPoint();
        return PropertyExecutor::execute(s, op, config);
    }
}