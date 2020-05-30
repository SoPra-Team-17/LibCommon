/**
 * @file   ActionExecutor_Movement.cpp
 * @author Dominik Authaler
 * @date   28.04.2020 (creation)
 * @brief  Definition of the execution method for movement operations.
 */

#include "ActionExecutor.hpp"

namespace spy::gameplay {
    std::shared_ptr<const BaseOperation> ActionExecutor::executeMovement(State &s, const Movement &op) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());
        character->subMovePoint();

        // search for character at target position
        auto charTarget = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                       [&op](const character::Character &c) {
                                           return c.getCoordinates() == op.getTarget();
                                       });

        if (charTarget != s.getCharacters().end()) {
            // characters need to swap places
            charTarget->setCoordinates(op.getFrom());
        }

        // special treatment for the cat
        if (s.getCatCoordinates().has_value() && s.getCatCoordinates().value() == op.getTarget()) {
            s.setCatCoordinates(op.getFrom());
        }

        // special treatment for the janitor
        if (s.getJanitorCoordinates().has_value() && s.getJanitorCoordinates().value() == op.getTarget()) {
            s.setJanitorCoordinates(op.getFrom());
        }

        character->setCoordinates(op.getTarget());

        auto gadget = s.getMap().getField(op.getTarget()).getGadget();
        if (gadget.has_value()) {
            // pick up gadget
            character->addGadget(gadget.value());
            s.getMap().getField(op.getTarget()).removeGadget();
        }

        auto retOp = std::make_shared<Movement>(op);
        retOp->setSuccessful(true);

        return retOp;
    }
}
