/**
* @file   BangAndBurn.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  implementation of bang and burn property execution
*/

#include "PropertyExecutor.hpp"

namespace spy::gameplay {
    std::shared_ptr<const BaseOperation> PropertyExecutor::executeBangAndBurn(State &s, const PropertyAction &a) {
        s.getMap().getField(a.getTarget()).setDestroyed(true);

        auto retOp = std::make_shared<PropertyAction>(a);
        retOp->setSuccessful(true);

        return retOp;
    }
}
