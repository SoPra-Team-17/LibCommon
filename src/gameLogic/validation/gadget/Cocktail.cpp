/**
 * @file   Cocktail.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of cocktail gadget validation.
 */


#include "GadgetValidator.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateCocktail(const State &s, GadgetAction a) {

        auto character = s.getCharacters().findByUUID(a.getCharacterId());

        auto hasCocktail = spy::util::GameLogicUtils::characterHasGadget(s, a.getCharacterId(),
                                                                         spy::gadget::GadgetEnum::COCKTAIL);

        if (Movement::getMoveDistance(a.getTarget(), character->getCoordinates().value()) > 1) {
            return false;
        }

        if (s.getMap().getField(a.getTarget()).getFieldState() == scenario::FieldStateEnum::BAR_TABLE) {
            // character is standing next to a bar table
            if (spy::util::GameLogicUtils::hasCocktail(s, a.getTarget())) {
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
        return spy::util::GameLogicUtils::personOnNeighbourField(s, a.getTarget(), character->getCoordinates().value());
    }
}