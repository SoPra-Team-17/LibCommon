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

        // check if character has gadget
        auto gadget = op.getGadget();
        bool hasGadget = spy::util::GadgetUtils::characterHasGadget(s, op.getCharacterId().value(),
                                                                    op.getGadget());
        if (!hasGadget) {
            return false;
        }

        return GadgetValidator::validate(s, op);
    }
}