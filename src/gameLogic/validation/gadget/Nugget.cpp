/**
* @file   Nugget.cpp
* @author Marco Deuscher
* @date   28.04.2020 (creation)
* @brief  Implementation of nugget gadget validation.
*/

#include "GadgetValidator.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateNugget(const State &s, GadgetAction a) {
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        return spy::util::GameLogicUtils::personOnNeighboringField(s, a.getTarget(), character->getCoordinates().value());
    }
}