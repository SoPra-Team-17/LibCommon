/**
 * @file   LaserCompact.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of mole die gadget validation.
 */

#include "datatypes/gameplay/Movement.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateMoleDie(const State &s, GadgetAction a) {
        //check if target is wall
        bool isWall = (s.getMap().getField(a.getTarget()).getFieldState() == scenario::FieldStateEnum::WALL);
        if (isWall) {
            return false;
        }

        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        auto distance = Movement::getMoveDistance(a.getTarget(), character->getCoordinates().value());
        // todo check if distance <= moleDieRange (not included in state)
        unsigned int moleDieRange = 10;


        bool lineOfSightFree = s.getMap().isLineOfSightFree(a.getTarget(), character->getCoordinates().value());

        return lineOfSightFree && distance <= moleDieRange;
    }
}
