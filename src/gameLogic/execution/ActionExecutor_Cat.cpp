//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    std::shared_ptr<const BaseOperation> ActionExecutor::executeCat(State &s, const CatAction &op) {
        s.setCatCoordinates(op.getTarget());

        auto retOp = std::make_shared<CatAction>(op);
        retOp->setSuccessful(true);

        return retOp;
    }
}