/**
 * @file   RocketPen.cpp
 * @author Marco Deuscher
 * @date   28.04.2020 (creation)
 * @brief  Implementation of rocket pen gadget validation.
 */

#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateRocketPen(const State &s, GadgetAction a) {
        // check if target is in line of sight of character
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        bool lineOfSightFree = s.getMap().isLineOfSightFree(character->getCoordinates().value(), a.getTarget());
        return lineOfSightFree;
    }
}