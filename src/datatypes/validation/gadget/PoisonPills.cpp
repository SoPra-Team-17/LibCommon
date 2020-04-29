/**
 * @file   PoisonPills.cpp
 * @author Marco Deuscher
 * @date   28.04.2020 (creation)
 * @brief  Implemenation of poison pills gadget validation.
 */

#include "datatypes/gameplay/Movement.hpp"
#include "util/GadgetUtils.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validatePoisonPills(const State &s, GadgetAction a) {
        using spy::gadget::GadgetEnum;

        // check if target inside map
        if (!s.getMap().isInside(a.getTarget())) {
            return false;
        }

        // check if character has poisonous pills
        bool characterHasPills = spy::util::GadgetUtils::characterHasGadget(s, a.getCharacterId().value(),
                                                                            GadgetEnum::POISON_PILLS);

        // check if target contains cocktail
        bool targetHasCocktail = spy::util::GadgetUtils::hasCocktail(s, a.getTarget());
        // check if target is adjacent field
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        auto distance = gameplay::Movement::getMoveDistance(a.getTarget(), character->getCoordinates().value());

        return targetHasCocktail && distance == 1 && characterHasPills;
    }
}
