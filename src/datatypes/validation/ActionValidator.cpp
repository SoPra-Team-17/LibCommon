//
// Created by Carolin on 29.04.2020.
//

#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validate(const State &s, std::shared_ptr<const BaseOperation> op) {
        switch (op->getType()) {
            case spy::gameplay::OperationEnum::MOVEMENT:
                return ActionValidator::validateMovement(s, *std::dynamic_pointer_cast<const gameplay::Movement>(op));
            case gameplay::OperationEnum::GADGET_ACTION:
                return ActionValidator::validateGadgetAction(s,
                                                             *std::dynamic_pointer_cast<const gameplay::GadgetAction>(
                                                                     op));
            case gameplay::OperationEnum::GAMBLE_ACTION:
                return ActionValidator::validateGambleAction(s,
                                                             *std::dynamic_pointer_cast<const gameplay::GambleAction>(
                                                                     op));
            case gameplay::OperationEnum::PROPERTY_ACTION:
                return ActionValidator::validatePropertyAction(s,
                                                               *std::dynamic_pointer_cast<const gameplay::PropertyAction>(
                                                                       op));
            case gameplay::OperationEnum::EXFILTRATION:
                return ActionValidator::validateExfiltration(s,
                                                             *std::dynamic_pointer_cast<const gameplay::Exfiltration>(
                                                                     op));
            case OperationEnum::SPY_ACTION:
                return ActionValidator::validateSpyAction(s, *std::dynamic_pointer_cast<const gameplay::SpyAction>(op));
            case OperationEnum::CAT_ACTION:
                return ActionValidator::validateCatAction(s, *std::dynamic_pointer_cast<const gameplay::CatAction>(op));
            case OperationEnum::JANITOR_ACTION:
                return ActionValidator::validateJanitorAction(s,
                                                              *std::dynamic_pointer_cast<const gameplay::JanitorAction>(
                                                                      op));
            case OperationEnum::RETIRE:
                return ActionValidator::validateRetireAction(s,
                                                             *std::dynamic_pointer_cast<const gameplay::RetireAction>(
                                                                     op));
            default:
                throw std::runtime_error("Validate for this action has not been implemented");

        }
    }
}
