/**
 * @file   GasGloss.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implemenation of gas gloss gadget validation.
 */


#include "util/GadgetUtils.hpp"
#include "datatypes/gameplay/Movement.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateGasGloss(const State &s, GadgetAction a) {
        using spy::gadget::GadgetEnum;

        // check if target inside map
        if (!s.getMap().isInside(a.getTarget())) {
            return false;
        }

        // check if character has laser compact
        bool hasGasGloss = spy::util::GadgetUtils::characterHasGadget(s, a.getCharacterId().value(),
                                                                      GadgetEnum::GAS_GLOSS);
        if (!hasGasGloss) {
            return false;
        }

        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        auto distance = Movement::getMoveDistance(character->getCoordinates().value(), a.getTarget());
        if (distance > 1) {
            return false;
        }

        // check if person on target field
        auto person = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                   [&a](const character::Character &c) {
                                       return c.getCoordinates() == a.getTarget();
                                   });
        return !(person == s.getCharacters().end());

    }
}
