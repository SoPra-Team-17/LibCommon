/**
* @file   Jetpack.cpp
* @author Marco Deuscher
* @date   28.04.2020 (creation)
* @brief  Implemenation of jetpack gadget validation.
*/

#include "util/GadgetUtils.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateJetpack(const State &s, GadgetAction a) {
        // check if target field is free
        return s.getMap().getField(a.getTarget()).getFieldState() == scenario::FieldStateEnum::FREE;
    }

}

