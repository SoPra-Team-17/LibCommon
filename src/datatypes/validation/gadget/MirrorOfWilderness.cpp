/**
 * @file   MirrorOfWilderness.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of mirror of wilerness gadget validation.
 */

#include "GadgetValidator.hpp"
#include "util/GadgetUtils.hpp"

namespace spy::gameplay{

    bool GadgetValidator::validateMirrorOfWilderness(const State &s, GadgetAction a) {
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        return spy::util::GadgetUtils::personOnNeighboringField(s, a.getTarget(), character->getCoordinates().value());
    }

}