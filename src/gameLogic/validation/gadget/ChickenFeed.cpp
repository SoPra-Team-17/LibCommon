/**
 * @file   ChickenFeed.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of chicken feed gadget validation.
 */


#include "GadgetValidator.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateChickenFeed(const State &s, GadgetAction a) {
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        return spy::util::GameLogicUtils::personOnNeighboringField(s, a.getTarget(), character->getCoordinates().value());
    }
}