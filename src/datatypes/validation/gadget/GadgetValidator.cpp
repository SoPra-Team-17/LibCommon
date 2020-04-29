//
// Created by jonas on 28.04.20.
//

#include "GadgetValidator.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validate(const State &s, GadgetAction op) {
        using gadget::GadgetEnum;
        // TODO implement
        switch (op.getGadget()) {
            case GadgetEnum::ROCKET_PEN:
                return GadgetValidator::validateRocketPen(s, op);

            case GadgetEnum::HAIRDRYER:
                return GadgetValidator::validateHairdryer(s, op);

            default:
                return false;
        }
    }
}