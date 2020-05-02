//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"

namespace spy::gameplay {
    bool ActionExecutor::executeMovement(State &s, const Movement &op) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());

        // search for character at target position
        auto charTarget = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                       [&op](const character::Character &c) {
                                           return c.getCoordinates() == op.getTarget();
                                       });

        if (charTarget != s.getCharacters().end()) {
            // characters need to swap places
            charTarget->setCoordinates(op.getFrom());
        }

        character->setCoordinates(op.getTarget());

        auto gadget = s.getMap().getField(op.getTarget()).getGadget();
        if (gadget.has_value()) {
            // pick up gadget
            character->addGadget(gadget.value());
            s.getMap().getField(op.getTarget()).removeGadget();
        }

        return true;
    }
}
