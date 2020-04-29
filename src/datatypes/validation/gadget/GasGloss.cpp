/**
 * @file   GasGloss.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implemenation of gas gloss gadget validation.
 */


#include "datatypes/gameplay/Movement.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateGasGloss(const State &s, GadgetAction a) {
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        auto distance = Movement::getMoveDistance(character->getCoordinates().value(), a.getTarget());
        if (distance > 1) {
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
