//
// Created by jonas on 28.04.20.
//

#include <util/GameLogicUtils.hpp>
#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validateSpyAction(const State &s, const spy::gameplay::SpyAction& op) {
        // check if target inside map
        if (!s.getMap().isInside(op.getTarget())) {
            return false;
        }

        auto character = s.getCharacters().findByUUID(op.getCharacterId());
        // check if character has enough action points
        if (character->getActionPoints() <= 0) {
            return false;
        }

        return spy::util::GameLogicUtils::personOnNeighbourField(s, op.getTarget(), character->getCoordinates().value());
    }
}