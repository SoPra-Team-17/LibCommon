/**
* @file   PropertyValidator.cpp
* @author Carolin
* @date   06.05.2020 (creation)
* @brief  Implementation of property validation
*/

#include "PropertyValidator.hpp"

namespace spy::gameplay {

    bool spy::gameplay::PropertyValidator::validate(const spy::gameplay::State &s, const spy::gameplay::PropertyAction &a) {
        switch(a.getUsedProperty()) {
            case character::PropertyEnum::BANG_AND_BURN:
                return PropertyValidator::validateBangAndBurn(s, a);
            case character::PropertyEnum::OBSERVATION:
                return PropertyValidator::validateObservation(s, a);
            default:
                break;
        }
        return false;
    }

}
