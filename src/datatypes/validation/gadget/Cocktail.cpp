/**
 * @file   Cocktail.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of cocktail gadget validation.
 */


#include "GadgetValidator.hpp"
#include "util/GadgetUtils.hpp"

#include <iostream>

namespace spy::gameplay {

    bool GadgetValidator::validateCocktail(const State &s, GadgetAction a) {

        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());

        auto hasCocktail = spy::util::GadgetUtils::characterHasGadget(s, a.getCharacterId().value(),
                                                                 spy::gadget::GadgetEnum::COCKTAIL);
        if (s.getMap().getField(a.getTarget()).getFieldState() == scenario::FieldStateEnum::BAR_TABLE) {
            if (spy::util::GadgetUtils::hasCocktail(s, a.getTarget())) {
                return !hasCocktail;
            } else {
                return false;
            }
        } else if (!hasCocktail) {
            return false;
        }

        if (character->getCoordinates().value() == a.getTarget()) {
            // drink cocktail
            return true;
        }

        // check if person on neighboring field
        return spy::util::GadgetUtils::personOnNeighboringField(s, a.getTarget(), character->getCoordinates().value());
    }
}