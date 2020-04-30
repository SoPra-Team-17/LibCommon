/**
 * @file   FogTin.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of fog tin gadget validation.
 */

#include "datatypes/gameplay/Movement.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateFogTin(const State &s, GadgetAction a) {
        // check if target field is wall
        bool targetIsWall = (s.getMap().getField(a.getTarget()).getFieldState() == scenario::FieldStateEnum::WALL);
        if (targetIsWall) {
            return false;
        }

        // check range and LoS
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        auto distance = Movement::getMoveDistance(character->getCoordinates().value(), a.getTarget());
        // todo hard coded range
        unsigned int fogTinRange = 10;

        bool lineOfSightFree = s.getMap().isLineOfSightFree(character->getCoordinates().value(), a.getTarget());

        return lineOfSightFree && distance <= fogTinRange;
    }
}
