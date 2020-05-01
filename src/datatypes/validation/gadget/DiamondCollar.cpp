/**
 * @file   DiamondCollar.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of diamond collar gadget validation.
 */

#include "GadgetValidator.hpp"
#include "util/GadgetUtils.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateDiamondCollar(const State &s, GadgetAction a) {
        // check if cat is on neighboring field
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        auto distance = Movement::getMoveDistance(character->getCoordinates().value(), a.getTarget());

        return distance == 1 && a.getTarget() == s.getCatCoordinates();
    }
}
