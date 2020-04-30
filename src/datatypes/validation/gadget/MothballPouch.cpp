/**
 * @file   MothballPouch.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of mothball pouch gadget validation.
 */

#include "datatypes/gameplay/Movement.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateMothballPouch(const State &s, GadgetAction a) {
        // check if target field is fireplace
        bool targetIsFireplace = (s.getMap().getField(a.getTarget()).getFieldState() == scenario::FieldStateEnum::FIREPLACE);
        if (!targetIsFireplace){
            return false;
        }

        // check distance and line of sight
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        auto distance = Movement::getMoveDistance(character->getCoordinates().value(), a.getTarget());
        // todo range hardcoded
        unsigned int mothballRange = 10;

        bool lineOfSightFree = s.getMap().isLineOfSightFree(character->getCoordinates().value(), a.getTarget());

        return lineOfSightFree && distance <= mothballRange;
    }
}
