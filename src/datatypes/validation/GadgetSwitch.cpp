//
// Created by jonas on 28.04.20.
//

#include <datatypes/validation/gadget/GadgetValidator.hpp>
#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validate(const State &s, GadgetAction op) {
        using gadget::GadgetEnum;
        // TODO implement
        switch (op.getGadget()) {
            case GadgetEnum::ROCKET_PEN:
                return GadgetValidator::validateRocketPen(s, op);
            default:
                return false;
        }
    }
}