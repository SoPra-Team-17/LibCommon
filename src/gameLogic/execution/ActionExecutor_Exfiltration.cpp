//
// Created by jonas on 28.04.20.
//

#include "ActionExecutor.hpp"
#include <util/GameLogicUtils.hpp>

namespace spy::gameplay {
    bool ActionExecutor::executeExfiltration(State &s, const Exfiltration &op) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());

        // search for character at target position
        auto charTarget = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                       [&op](const character::Character &c) {
                                           return c.getCoordinates() == op.getTarget();
                                       });

        if (charTarget != s.getCharacters().end()) {
            // charTarget has to be placed on a random free neighbouring field
            charTarget->setCoordinates(util::GameLogicUtils::getRandomCharacterFreeNeighbouringField(s, op.getTarget()));
        }

        // character has to be exfiltrated
        character->setCoordinates(op.getTarget());
        character->setHealthPoints(1);
        return true;
    }
}