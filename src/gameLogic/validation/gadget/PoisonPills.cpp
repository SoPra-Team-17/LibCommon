/**
 * @file   PoisonPills.cpp
 * @author Marco Deuscher
 * @date   28.04.2020 (creation)
 * @brief  Implementation of poison pills gadget validation.
 */

#include "datatypes/gameplay/Movement.hpp"
#include "util/GameLogicUtils.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validatePoisonPills(const State &s, GadgetAction a) {
        // check if target contains cocktail
        bool targetHasCocktail = spy::util::GameLogicUtils::hasCocktail(s, a.getTarget());
        // check if target is adjacent field
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        auto distance = gameplay::Movement::getMoveDistance(a.getTarget(), character->getCoordinates().value());

        return (targetHasCocktail && distance <= 1);
    }
}
