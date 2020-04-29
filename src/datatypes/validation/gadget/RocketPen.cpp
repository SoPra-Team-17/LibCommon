/**
 * @file   LaserCompact.cpp
 * @author Marco Deuscher
 * @date   28.04.2020 (creation)
 * @brief  Implemenation of rocket pen gadget validation.
 */

#include "GadgetValidator.hpp"
#include "util/GadgetUtils.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateRocketPen(const State &s, GadgetAction a) {
        using spy::gadget::GadgetEnum;

        // check if target inside map
        if (!s.getMap().isInside(a.getTarget())) {
            return false;
        }

        // check if character has laser compact
        bool hasRocketPen = spy::util::GadgetUtils::characterHasGadget(s, a.getCharacterId().value(),
                                                                       GadgetEnum::ROCKET_PEN);
        if (!hasRocketPen) {
            return false;
        }

        // check if target is in line of sight of character
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        bool lineOfSightFree = s.getMap().isLineOfSightFree(character->getCoordinates().value(), a.getTarget());
        return lineOfSightFree;
    }
}