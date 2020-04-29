//
// Created by Carolin on 29.04.2020.
//

#include "BaseOperation.hpp"
#include <utility>

namespace spy::gameplay {

    BaseOperation::BaseOperation(OperationEnum type, bool successful, const util::Point &target) :
            type{type},
            successful{successful},
            target{target} {}

    OperationEnum BaseOperation::getType() const {
        return type;
    }

    bool BaseOperation::isSuccessful() const {
        return successful;
    }

    const util::Point &BaseOperation::getTarget() const {
        return target;
    }
}
