/**
* @file   BangAndBurn.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  implementation of bang and burn property execution
*/

#include "PropertyExecutor.hpp"

namespace spy::gameplay {
    bool PropertyExecutor::executeBangAndBurn(State &s, const PropertyAction &a) {
        s.getMap().getField(a.getTarget()).setDestroyed(true);
        return true;
    }
}
