/**
* @file   WiretapWithEarplugs.cpp
* @author Marco Deuscher
* @date   28.04.2020 (creation)
* @brief  Implementation of wiretap with earplugs gadget validation.
*/

#include "GadgetValidator.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateWiretapWithEarplugs(const State &s, GadgetAction a) {
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        return spy::util::GameLogicUtils::personOnNeighboringField(s, a.getTarget(), character->getCoordinates().value());
    }
}
