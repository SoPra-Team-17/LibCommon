/**
 * @file   GasGloss.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of gas gloss gadget validation.
 */


#include <util/GadgetUtils.hpp>
#include "datatypes/gameplay/Movement.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateGasGloss(const State &s, GadgetAction a) {
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        auto distance = Movement::getMoveDistance(character->getCoordinates().value(), a.getTarget());
        if (distance > 1) {
            return false;
        }

        // check if person on target field
        return util::GadgetUtils::isPersonOnField(s, a.getTarget());
    }
}
