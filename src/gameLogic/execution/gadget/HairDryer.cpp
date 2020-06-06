/**
* @file   HairDryer.cpp
* @author Jonas Otto
* @date   28.04.20 (creation)
* @date   rewritten 05.05.20 by Marco Deuscher
* @brief  Implementation of HairDryer gadget execution
*/

#include "GadgetExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {
    bool GadgetExecutor::executeHairDryer(State &s, const GadgetAction &action) {
        // Search character at target location
        auto charTarget = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), action.getTarget());

        if (charTarget->hasProperty(character::PropertyEnum::CONSTANT_CLAMMY_CLOTHES)) {
            return false;
        }

        // Remove CLAMMY_CLOTHES (Lastenheft: "Klamme Klamotten") property
        charTarget->getProperties().erase(character::PropertyEnum::CLAMMY_CLOTHES);

        return true;
    }
}