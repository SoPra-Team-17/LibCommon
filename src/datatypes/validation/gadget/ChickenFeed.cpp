/**
 * @file   ChickenFeed.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of chicken feed gadget validation.
 */


#include "GadgetValidator.hpp"
#include "util/GadgetUtils.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateChickenFeed(const State &s, GadgetAction a) {
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        return spy::util::GadgetUtils::personOnNeighboringField(s, a.getTarget(), character->getCoordinates().value());
    }
}