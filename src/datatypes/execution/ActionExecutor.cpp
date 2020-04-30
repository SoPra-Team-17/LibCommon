//
// Created by Carolin on 29.04.2020.
//

#include "ActionExecutor.hpp"

namespace spy::gameplay {

    bool ActionExecutor::execute(State &s, const std::shared_ptr<const BaseOperation> op) {
        switch (op->getType()) {
            case spy::gameplay::OperationEnum::MOVEMENT:
                return ActionExecutor::executeMovement(s, *std::dynamic_pointer_cast<const gameplay::Movement>(op));
            case gameplay::OperationEnum::GADGET_ACTION:
                return ActionExecutor::executeGadget(s, *std::dynamic_pointer_cast<const gameplay::GadgetAction>(op));
            case gameplay::OperationEnum::GAMBLE_ACTION:
                return ActionExecutor::executeGamble(s, *std::dynamic_pointer_cast<const gameplay::GambleAction>(op));
            case gameplay::OperationEnum::PROPERTY_ACTION:
                return ActionExecutor::executeProperty(
                        s,
                        *std::dynamic_pointer_cast<const gameplay::PropertyAction>(op));
            case gameplay::OperationEnum::EXFILTRATION:
                return ActionExecutor::executeExfiltration(
                        s, *std::dynamic_pointer_cast<const gameplay::Exfiltration>(op));
            case OperationEnum::INVALID:
                break;
            case OperationEnum::SPY_ACTION:
                break;
            case OperationEnum::CAT_ACTION:
                break;
            case OperationEnum::JANITOR_ACTION:
                break;
            case OperationEnum::RETIRE:
                break;
        }
        throw std::runtime_error("Execute for this action has not been implemented");
    }
}
