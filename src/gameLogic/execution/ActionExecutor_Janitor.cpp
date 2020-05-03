//
// Created by jonas on 28.04.20.
//
#include <util/GameLogicUtils.hpp>
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    bool ActionExecutor::executeJanitor(State &s, const JanitorAction &op) {
        s.setJanitorCoordinates(op.getTarget());
        util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), op.getTarget())->setCoordinates(
                util::Point{-1, -1});
        return true;
    }
}