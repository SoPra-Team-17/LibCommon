//
// Created by jonas on 28.04.20.
//

#include <datatypes/validation/gadget/GadgetValidator.hpp>
#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validateGadgetAction(const State &s, GadgetAction op) {
        return GadgetValidator::validate(s, op);
    }
}