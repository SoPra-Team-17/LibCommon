//
// Created by jonas on 28.04.20.
//

#include <util/GameLogicUtils.hpp>
#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validateSpyAction(const State &s, const spy::gameplay::SpyAction &op) {
        using spy::character::PropertyEnum;

        // check if target inside map
        if (!s.getMap().isInside(op.getTarget())) {
            return false;
        }

        auto character = s.getCharacters().findByUUID(op.getCharacterId());
        // check if character has enough action points
        if (character->getActionPoints() <= 0) {
            return false;
        }

        // check if character is inside fog
        bool isFieldFoggy = s.getMap().getField(character->getCoordinates().value()).isFoggy();
        if (isFieldFoggy) {
            return false;
        }

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

        bool hasMoleDie = character->hasGadget(spy::gadget::GadgetEnum::MOLEDIE);
        bool hasFlapsAndSeals = character->hasProperty(character::PropertyEnum::FLAPS_AND_SEALS);

        return hasSafe && (distance == 2) && hasFlapsAndSeals && !hasMoleDie;
    }
}