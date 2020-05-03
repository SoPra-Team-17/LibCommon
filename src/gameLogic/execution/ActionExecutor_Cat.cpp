//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    bool ActionExecutor::executeCat(State &s, const CatAction &op) {
        s.setCatCoordinates(op.getTarget());
        return true;
    }
}