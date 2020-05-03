/**
 * @file   LaserCompact.cpp
 * @author Marco Deuscher
 * @date   28.04.2020 (creation)
 * @brief  Implementation of laser compact gadget validation.
 */

#include "util/GameLogicUtils.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateLaserCompact(const State &s, GadgetAction a) {
        // check if target contains cocktail
        bool targetHasCocktail = spy::util::GameLogicUtils::hasCocktail(s, a.getTarget());

        // check if target is in line of sight of character
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        bool lineOfSightFree = s.getMap().isLineOfSightFree(a.getTarget(), character->getCoordinates().value());

        return lineOfSightFree && targetHasCocktail;
    }
}
