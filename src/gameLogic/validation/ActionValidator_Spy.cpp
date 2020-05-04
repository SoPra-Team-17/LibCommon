//
// Created by jonas on 28.04.20.
//

#include <util/GameLogicUtils.hpp>
#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validateSpyAction(const State &s, const spy::gameplay::SpyAction& op) {
        using spy::character::PropertyEnum;

        // check if target inside map
        if (!s.getMap().isInside(op.getTarget())) {
            return false;
        }
        auto character = s.getCharacters().findByUUID(op.getCharacterId());
        bool spyOnPerson = spy::util::GameLogicUtils::personOnNeighbourField(s, op.getTarget(),
                                                                               character->getCoordinates().value());
        if (spyOnPerson) {
            return true;
        }

        // check if target field has safe
        bool hasSafe = s.getMap().getField(op.getTarget()).getFieldState() == scenario::FieldStateEnum::SAFE;
        // check distance to field
        auto distance = Movement::getMoveDistance(op.getTarget(), character->getCoordinates().value());
        if (hasSafe && distance == 1) {
            return true;
        }

        return hasSafe && (distance == 2) && character->hasProperty(character::PropertyEnum::FLAPS_AND_SEALS);
    }
}