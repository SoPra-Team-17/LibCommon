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

        auto targetUUID = spy::util::GameLogicUtils::getPersonOnNeighbourField(s, a.getTarget(),
                                                                               character->getCoordinates().value());

        if (!targetUUID.has_value()) {
            // nugget can only be used against characters
            return false;
        } else {
            // nugget can only be used against characters of another faction
            auto targetChar = s.getCharacters().findByUUID(targetUUID.value());
            return (targetChar->getFaction() != character->getFaction());
        }
    }
}