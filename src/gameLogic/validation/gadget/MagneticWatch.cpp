/**
 * @file   MagneticWatch.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  Implementation of magnetic watch gadget validation.
 */


#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateMagneticWatch(const State &/*s*/, GadgetAction /*a*/) {
        // magnetic watch cannot be used actively, has passive effect!
        return false;
    }
}