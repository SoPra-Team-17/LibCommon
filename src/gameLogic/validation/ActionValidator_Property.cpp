//
// Created by jonas on 28.04.20.
//

#include <util/GadgetUtils.hpp>
#include <datatypes/character/PropertyEnum.hpp>
#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validatePropertyAction(const State &s, const spy::gameplay::PropertyAction &op) {
        switch (op.getUsedProperty()) {
            case character::PropertyEnum::BANG_AND_BURN: {
                auto character = s.getCharacters().findByUUID(op.getCharacterId());
                return character->hasProperty(character::PropertyEnum::BANG_AND_BURN) &&
                       Movement::getMoveDistance(op.getTarget(), character->getCoordinates().value()) == 1 &&
                       s.getMap().getField(op.getTarget()).getFieldState() == scenario::FieldStateEnum::ROULETTE_TABLE;
            }
            case character::PropertyEnum::OBSERVATION: {
                auto character = s.getCharacters().findByUUID(op.getCharacterId());
                return character->hasProperty(character::PropertyEnum::OBSERVATION) &&
                        s.getMap().isLineOfSightFree(op.getTarget(), character->getCoordinates().value());
            }
            default:
                // property not usable as action
                break;
        }
        return false;
    }
}