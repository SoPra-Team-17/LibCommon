//
// Created by Carolin on 29.04.2020.
//

#include "ActionExecutor.hpp"

namespace spy::gameplay {

    bool ActionExecutor::execute(State &s, const std::shared_ptr<Operation> &op) {
        switch (op->getType()) {
            case spy::gameplay::OperationEnum::MOVEMENT:
                return ActionExecutor::execute(s, *std::dynamic_pointer_cast<gameplay::Movement>(op));
            case gameplay::OperationEnum::GADGET_ACTION:
                return ActionExecutor::execute(s, *std::dynamic_pointer_cast<gameplay::GadgetAction>(op));
            case gameplay::OperationEnum::GAMBLE_ACTION:
                return ActionExecutor::execute(s, *std::dynamic_pointer_cast<gameplay::GambleAction>(op));
            case gameplay::OperationEnum::PROPERTY_ACTION:
                return ActionExecutor::execute(s, *std::dynamic_pointer_cast<gameplay::PropertyAction>(op));
            case gameplay::OperationEnum::EXFILTRATION:
                return ActionExecutor::execute(s, *std::dynamic_pointer_cast<gameplay::Exfiltration>(op));
            default:
                return ActionExecutor::execute(s, *op);
        }
    }
}
