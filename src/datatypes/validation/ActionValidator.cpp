//
// Created by Carolin on 29.04.2020.
//

#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validate(const State &s, const std::shared_ptr<Operation>& op) {
        switch (op->getType()) {
            case spy::gameplay::OperationEnum::MOVEMENT:
                return ActionValidator::validate(s, *std::dynamic_pointer_cast<gameplay::Movement>(op));
            case gameplay::OperationEnum::GADGET_ACTION:
                return ActionValidator::validate(s, *std::dynamic_pointer_cast<gameplay::GadgetAction>(op));
            case gameplay::OperationEnum::GAMBLE_ACTION:
                return ActionValidator::validate(s, *std::dynamic_pointer_cast<gameplay::GambleAction>(op));
            case gameplay::OperationEnum::PROPERTY_ACTION:
                return ActionValidator::validate(s, *std::dynamic_pointer_cast<gameplay::PropertyAction>(op));
            case gameplay::OperationEnum::EXFILTRATION:
                return ActionValidator::validate(s, *std::dynamic_pointer_cast<gameplay::Exfiltration>(op));
            default:
                return ActionValidator::validate(s, *op);
        }
    }
}
