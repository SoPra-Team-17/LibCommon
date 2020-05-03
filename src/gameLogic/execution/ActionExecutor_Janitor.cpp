//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    bool ActionExecutor::executeJanitor(State &s, const JanitorAction &op) {
        s.setJanitorCoordinates(op.getTarget());
        s.getCharacters().getByCoordinates(op.getTarget())->setCoordinates(util::Point{-1, -1});
        return true;
    }
}