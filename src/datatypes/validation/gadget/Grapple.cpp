/**
* @file   Grapple.cpp
* @author Marco Deuscher
* @date   28.04.2020 (creation)
* @brief  Implementation of grapple gadget validation.
*/

#include "GadgetValidator.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateGrapple(const State &s, GadgetAction a) {
        // check range and LoS
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        auto distance = Movement::getMoveDistance(character->getCoordinates().value(), a.getTarget());
        //todo grapple range hardcoded
        unsigned int grappleRange = 10;

        bool lineOfSightFree = s.getMap().isLineOfSightFree(character->getCoordinates().value(), a.getTarget());

        // target field has gadget
        auto gadget = s.getMap().getField(a.getTarget()).getGadget();

        return gadget.has_value() && lineOfSightFree && distance <= grappleRange;
    }
}
