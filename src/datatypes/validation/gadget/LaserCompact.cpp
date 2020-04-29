/**
 * @file   LaserCompact.cpp
 * @author Marco Deuscher
 * @date   28.04.2020 (creation)
 * @brief  Implemenation of laser compact gadget validation.
 */

#include "util/GadgetUtils.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateLaserCompact(const State &s, GadgetAction a) {
        // check if target contains cocktail
        bool targetHasCocktail = spy::util::GadgetUtils::hasCocktail(s, a.getTarget());

        // check if target is in line of sight of character
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        bool lineOfSightFree = s.getMap().isLineOfSightFree(a.getTarget(), character->getCoordinates().value());

        return lineOfSightFree && targetHasCocktail;
    }
}
