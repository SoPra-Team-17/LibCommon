//
// Created by jonas on 28.04.20.
//

#include <util/GameLogicUtils.hpp>
#include <datatypes/character/PropertyEnum.hpp>
#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validatePropertyAction(const State &s, const spy::gameplay::PropertyAction &op) {
        using spy::gadget::GadgetEnum;


        // check if target inside map
        if (!s.getMap().isInside(op.getTarget())) {
            return false;
        }
      
        switch (op.getUsedProperty()) {
            case character::PropertyEnum::BANG_AND_BURN: {
                auto character = s.getCharacters().findByUUID(op.getCharacterId());
                return character->hasProperty(character::PropertyEnum::BANG_AND_BURN) &&
                       Movement::getMoveDistance(op.getTarget(), character->getCoordinates().value()) == 1 &&
                       s.getMap().getField(op.getTarget()).getFieldState() == scenario::FieldStateEnum::ROULETTE_TABLE;
            }
            case character::PropertyEnum::OBSERVATION: {
                // if character has mole die observation is deactivated
                auto character = s.getCharacters().findByUUID(op.getCharacterId());
                bool hasMoleDie = spy::util::GameLogicUtils::characterHasGadget(s, character->getCharacterId(),
                                                                                GadgetEnum::MOLEDIE);
                if (hasMoleDie) {
                    return false;
                }

                return character->hasProperty(character::PropertyEnum::OBSERVATION) &&
                       s.getMap().isLineOfSightFree(op.getTarget(), character->getCoordinates().value());
            }
            default:
                throw std::invalid_argument("Property is not usable as action");
        }
    }
}