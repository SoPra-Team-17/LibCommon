//
// Created by jonas on 28.04.20.
//
#include <gameLogic/execution/gadget/GadgetExecutor.hpp>
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    std::shared_ptr<const BaseOperation>
    ActionExecutor::executeGadget(State &s, const GadgetAction &op, const MatchConfig &config) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());
        character->subActionPoint();
        auto success =  GadgetExecutor::execute(s, op, config);

        auto retOp = std::make_shared<GadgetAction>(op);
        retOp->setSuccessful(success);

        return retOp;
    }
}