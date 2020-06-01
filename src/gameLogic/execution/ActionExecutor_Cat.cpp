//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {
    std::shared_ptr<const BaseOperation> ActionExecutor::executeCat(State &s, const CatAction &op) {
        auto targetChar = spy::util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), op.getTarget());

        if (targetChar != s.getCharacters().end()) {
            // white cat and character swap places
            targetChar->setCoordinates(s.getCatCoordinates().value());
        } else if (s.getJanitorCoordinates().has_value() && s.getJanitorCoordinates().value() == op.getTarget()) {
            // white cat and janitor swap places
            s.setJanitorCoordinates(s.getCatCoordinates().value());
        }

        s.setCatCoordinates(op.getTarget());

        auto retOp = std::make_shared<CatAction>(op);
        retOp->setSuccessful(true);

        return retOp;
    }
}