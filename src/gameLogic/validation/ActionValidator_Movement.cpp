//
// Created by jonas on 28.04.20.
//

#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validateMovement(const State &s, spy::gameplay::Movement op) {
        if (Movement::getMoveDistance(op.getFrom(), op.getTarget()) > 1) {  // only one step is allowed per game rules
            return false;
        }

        auto character = s.getCharacters().findByUUID(op.getCharacterId());
        if (character == s.getCharacters().end()) {                            // specified character UUID is not valid
            return false;
        } else if (character->getCoordinates() != op.getFrom()) {       // doesn't match characters position
            return false;
        }

        return s.getMap().isAccessible(op.getTarget());
    }
}