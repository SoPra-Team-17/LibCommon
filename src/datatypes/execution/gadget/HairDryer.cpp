//
// Created by jonas on 28.04.20.
//
#include "GadgetExecutor.hpp"

namespace spy::gameplay {
    bool GadgetExecutor::executeHairDryer(State s, const GadgetAction &action) {
        // Search character at target location
        auto charTarget = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                       [&](const character::Character &c) {
                                           return c.getCoordinates() == action.getTarget();;
                                       });

        // Remove CLAMMY_CLOTHES (Lastenheft: "Klamme Klamotten") property
        charTarget->getProperties().erase(character::PropertyEnum::CLAMMY_CLOTHES);

        return true;
    }
}