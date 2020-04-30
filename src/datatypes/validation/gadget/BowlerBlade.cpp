/**
* @file   BowlerBlade.cpp
* @author Marco Deuscher
* @date   28.04.2020 (creation)
* @brief  Implementation of bowler blade gadget validation.
*/

#include "GadgetValidator.hpp"
#include "util/GadgetUtils.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateBowlerBlade(const State &s, GadgetAction a) {
        // check LoS
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        bool lineOfSightFree = spy::util::GadgetUtils::bowlerBladeLineOfSight(s, character->getCoordinates().value(),
                                                                              a.getTarget());
        // check range
        auto distance = Movement::getMoveDistance(character->getCoordinates().value(), a.getTarget());
        // todo distance is hardcoded
        unsigned int bowlerBladeDistance = 10;

        // check if there is a person on target field
        auto person = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                   [&a](const character::Character &c) {
                                       return c.getCoordinates() == a.getTarget();
                                   });
        bool personOnField = !(person == s.getCharacters().end());

        return personOnField && lineOfSightFree && distance <= bowlerBladeDistance;
    }
}

