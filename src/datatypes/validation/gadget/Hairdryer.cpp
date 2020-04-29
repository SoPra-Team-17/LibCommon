/**
* @file   Hairdryer.cpp
* @author Dominik Authaler
* @date   29.04.2020 (creation)
* @brief  Implementation of hairdryer gadget validation.
*/

#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateHairdryer(const State &s, GadgetAction a) {
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());

        // check range
        if (Movement::getMoveDistance(character->getCoordinates().value(), a.getTarget()) > 1) {
            return false;
        }

        // search for character at target position
        auto charTarget = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                       [&a](const character::Character &c) {
                                           return c.getCoordinates() == a.getTarget();
                                       });

        return (charTarget != s.getCharacters().end());
    }
}

