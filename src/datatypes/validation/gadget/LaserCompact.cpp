/**
 * @file   LaserCompact.cpp
 * @author Marco Deuscher
 * @date   28.04.2020 (creation)
 * @brief  Implemenation of laser compact gadget validation.
 */

#include "datatypes/gameplay/Movement.hpp"
#include "util/GadgetUtils.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay{
    bool GadgetValidator::validateLaserCompact(const State &s, GadgetAction a) {
        using spy::gadget::GadgetEnum;

        // check if target inside map
        if (!s.getMap().isInside(a.getTarget())) {
            return false;
        }

        // check if character has laser compact
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        auto gadgets = character->getGadgets();
        auto gadget = std::find_if(gadgets.begin(), gadgets.end(), [](const gadget::Gadget &g) {
            return g.getType() == GadgetEnum::LASER_COMPACT;
        });

        // check if target contains cocktail
        bool targetHasCocktail = spy::util::GadgetUtils::hasCocktail(s, a.getTarget());

        // check if target is in line of sight of character
        bool lineOfSightFree = s.getMap().isLineOfSightFree(a.getTarget(), character->getCoordinates().value());

        return lineOfSightFree && targetHasCocktail && gadget != gadgets.end();
    }
}
