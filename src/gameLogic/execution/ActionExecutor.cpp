/**
* @file   ActionExecutor.hpp
* @author Carolin
* @date   29.04.2020 (creation)
* @brief  Implementation of the static action execution class.
*/

#include "ActionExecutor.hpp"

namespace spy::gameplay {

    std::shared_ptr<const BaseOperation>
    ActionExecutor::execute(State &s, const std::shared_ptr<const BaseOperation> op, const MatchConfig &config) {
        switch (op->getType()) {
            case spy::gameplay::OperationEnum::MOVEMENT:
                return ActionExecutor::executeMovement(s, *std::dynamic_pointer_cast<const gameplay::Movement>(op));

            case gameplay::OperationEnum::GADGET_ACTION:
                return ActionExecutor::executeGadget(s, *std::dynamic_pointer_cast<const gameplay::GadgetAction>(op),
                                                     config);

            case gameplay::OperationEnum::GAMBLE_ACTION:
                return ActionExecutor::executeGamble(s, *std::dynamic_pointer_cast<const gameplay::GambleAction>(op));

            case gameplay::OperationEnum::PROPERTY_ACTION:
                return ActionExecutor::executeProperty(s,
                                                       *std::dynamic_pointer_cast<const gameplay::PropertyAction>(op),
                                                       config);

            case gameplay::OperationEnum::EXFILTRATION:
                return ActionExecutor::executeExfiltration(s, *std::dynamic_pointer_cast<const gameplay::Exfiltration>(
                        op));

            case OperationEnum::SPY_ACTION:
                return ActionExecutor::executeSpy(s, *std::dynamic_pointer_cast<const gameplay::SpyAction>(op), config);

            case OperationEnum::CAT_ACTION:
                return ActionExecutor::executeCat(s, *std::dynamic_pointer_cast<const gameplay::CatAction>(op));

            case OperationEnum::JANITOR_ACTION:
                return ActionExecutor::executeJanitor(s, *std::dynamic_pointer_cast<const gameplay::JanitorAction>(op));

            case OperationEnum::RETIRE:
                return ActionExecutor::executeRetire(s, *std::dynamic_pointer_cast<const gameplay::RetireAction>(op));

            default:
                throw std::invalid_argument("Execute for this action has not been implemented");
        }
    }
}
