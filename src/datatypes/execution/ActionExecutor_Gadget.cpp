//
// Created by jonas on 28.04.20.
//
#include <datatypes/execution/gadget/GadgetExecutor.hpp>
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    bool ActionExecutor::executeGadget(State &s, const GadgetAction &op) {
        return GadgetExecutor::execute(s, op);
    }
}