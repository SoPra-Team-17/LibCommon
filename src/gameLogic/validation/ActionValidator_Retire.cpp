//
// Created by jonas on 28.04.20.
//

#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validateRetireAction(const State &/*s*/, const spy::gameplay::RetireAction & /*op*/) {
        // retire action is always valid if it is turn of op->getCharacterId() which is validated in GameOperation message
        return true;
    }
}