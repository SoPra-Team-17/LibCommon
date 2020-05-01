//
// Created by jonas on 28.04.20.
//

#include <datatypes/validation/gadget/GadgetValidator.hpp>
#include <util/GadgetUtils.hpp>
#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validate(const State &s, GadgetAction op) {
        using spy::gadget::GadgetEnum;

        // check if target inside map
        if (!s.getMap().isInside(op.getTarget())) {
            return false;
        }

        // check if selected character exits and stands within the game field
        auto character = s.getCharacters().findByUUID(op.getCharacterId().value());
        if (character == s.getCharacters().end()
            || !character->getCoordinates().has_value()) {
            return false;
        }

        // check if character has gadget
        bool hasGadget = spy::util::GadgetUtils::characterHasGadget(s, op.getCharacterId().value(),
                                                                    op.getGadget());
        // picking up a cocktail is the only action that can be performed without having the gadget
        if (op.getGadget() != GadgetEnum::COCKTAIL && !hasGadget) {
            return false;
        }

        return GadgetValidator::validate(s, op);
    }
}