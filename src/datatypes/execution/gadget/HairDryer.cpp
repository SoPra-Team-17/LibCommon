//
// Created by jonas on 28.04.20.
//
#include "GadgetExecutor.hpp"

namespace spy::gameplay {
    bool GadgetExecutor::executeHairDryer(State s, const GadgetAction &action) {
        auto character = s.getCharacters().findByUUID(action.getCharacterId().value());
        auto target = action.getTarget();

        // Search character at target location
        auto charTarget = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                       [&](const character::Character &c) {
                                           return c.getCoordinates() == target;
                                       });

        charTarget->getProperties().erase(character::PropertyEnum::CLAMMY_CLOTHES);

        return true;
    }
}