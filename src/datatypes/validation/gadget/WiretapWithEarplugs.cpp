/**
* @file   WiretapWithEarplugs.cpp
* @author Marco Deuscher
* @date   28.04.2020 (creation)
* @brief  Implemenation of wiretap with earplugs gadget validation.
*/

#include "GadgetValidator.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateWiretapWithEarplugs(const State &s, GadgetAction a) {
        // check distance
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        auto distance = Movement::getMoveDistance(character->getCoordinates().value(), a.getTarget());
        if (distance != 1) {
            return false;
        }

        // check if person on target field
        auto person = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                   [&a](const character::Character &c) {
                                       return c.getCoordinates() == a.getTarget();
                                   });
        return !(person == s.getCharacters().end());
    }
}
