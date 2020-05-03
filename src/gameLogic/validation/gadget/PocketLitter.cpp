/**
 * @file   PocketLitter.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of mirror of wilerness gadget validation.
 */

#include "GadgetValidator.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay{

    bool GadgetValidator::validatePocketLitter(const State &/*s*/, GadgetAction /*a*/) {
        // pocket litter cannot be used actively, has passive property
        return false;
    }
}
