/**
* @file   ActionValidator.cpp
* @author Carolin
* @date   29.04.2020 (creation)
* @brief  Implementation of the static action validation class.
*/

#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validate(const State &s, std::shared_ptr<const BaseOperation> op, const MatchConfig &config) {
        switch (op->getType()) {
            case spy::gameplay::OperationEnum::MOVEMENT:
                return ActionValidator::validateMovement(s, *std::dynamic_pointer_cast<const gameplay::Movement>(op));
            case gameplay::OperationEnum::GADGET_ACTION:
                return ActionValidator::validateGadgetAction(s,
                                                             *std::dynamic_pointer_cast<const gameplay::GadgetAction>(
                                                                     op), config);
            case gameplay::OperationEnum::GAMBLE_ACTION:
                return ActionValidator::validateGambleAction(s,
                                                             *std::dynamic_pointer_cast<const gameplay::GambleAction>(
                                                                     op));
            case gameplay::OperationEnum::PROPERTY_ACTION:
                return ActionValidator::validatePropertyAction(s,
                                                               *std::dynamic_pointer_cast<const gameplay::PropertyAction>(
                                                                       op));
            case OperationEnum::SPY_ACTION:
                return ActionValidator::validateSpyAction(s, *std::dynamic_pointer_cast<const gameplay::SpyAction>(op));
            case OperationEnum::RETIRE:
                return ActionValidator::validateRetireAction(s,
                                                             *std::dynamic_pointer_cast<const gameplay::RetireAction>(
                                                                     op));
            default:
                throw std::invalid_argument("Validate for this action has not been implemented");

        }
    }
}
