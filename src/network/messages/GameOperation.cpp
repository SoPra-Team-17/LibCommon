//
// Created by jonas on 07.04.20.
//

#include <datatypes/validation/ActionValidator.hpp>
#include <utility>
#include "GameOperation.hpp"

namespace spy::network::messages {
    GameOperation::GameOperation() : MessageContainer{MessageTypeEnum::GAME_OPERATION, {}} {}

    GameOperation::GameOperation(spy::util::UUID playerId, std::shared_ptr<gameplay::Operation>  operation) :
            MessageContainer{MessageTypeEnum::GAME_OPERATION, playerId},
            operation{std::move(operation)} {}

    void to_json(nlohmann::json &j, const GameOperation &g) {
        MessageContainer::common_to_json(j, g);
        switch (g.operation->getType()) {
            case spy::gameplay::OperationEnum::MOVEMENT:
                j["operation"] = *std::dynamic_pointer_cast<gameplay::Movement>(g.operation);
                break;
            case gameplay::OperationEnum::GADGET_ACTION:
                j["operation"] = *std::dynamic_pointer_cast<gameplay::GadgetAction>(g.operation);
                break;
            case gameplay::OperationEnum::GAMBLE_ACTION:
                j["operation"] = *std::dynamic_pointer_cast<gameplay::GambleAction>(g.operation);
                break;
            case gameplay::OperationEnum::PROPERTY_ACTION:
                j["operation"] = *std::dynamic_pointer_cast<gameplay::PropertyAction>(g.operation);
                break;
            case gameplay::OperationEnum::EXFILTRATION:
                j["operation"] = *std::dynamic_pointer_cast<gameplay::Exfiltration>(g.operation);
                break;
            default:
                j["operation"] = *g.operation;
                break;
        }
    }

    void from_json(const nlohmann::json &j, GameOperation &g) {
        MessageContainer::common_from_json(j, g);
        j.at("operation").get_to(*g.operation);
        switch (g.operation->getType()) {
            case spy::gameplay::OperationEnum::MOVEMENT:
                g.operation = std::make_shared<gameplay::Operation>(j.at("operation").get<gameplay::Movement>());
                break;
            case gameplay::OperationEnum::GADGET_ACTION:
                g.operation = std::make_shared<gameplay::Operation>(j.at("operation").get<gameplay::GadgetAction>());
                break;
            case gameplay::OperationEnum::GAMBLE_ACTION:
                g.operation = std::make_shared<gameplay::Operation>(j.at("operation").get<gameplay::GambleAction>());
                break;
            case gameplay::OperationEnum::PROPERTY_ACTION:
                g.operation = std::make_shared<gameplay::Operation>(j.at("operation").get<gameplay::PropertyAction>());
                break;
            case gameplay::OperationEnum::EXFILTRATION:
                g.operation = std::make_shared<gameplay::Operation>(j.at("operation").get<gameplay::Exfiltration>());
                break;
            default:
                // do nothing
                break;
        }
    }

    const std::shared_ptr<gameplay::Operation>  &GameOperation::getOperation() const {
        return operation;
    }

    bool GameOperation::operator==(const GameOperation &rhs) const {
        return isEqual(rhs) &&
               operation == rhs.operation;
    }

    bool GameOperation::validate(RoleEnum playerRole, spy::gameplay::State &state) const {
        if (playerRole == spy::network::RoleEnum::INVALID ||
            playerRole == spy::network::RoleEnum::SPECTATOR) {
            return false;
        }

        spy::gameplay::OperationEnum operationType = operation->getType();
        if (operationType == spy::gameplay::OperationEnum::INVALID ||
            operationType == spy::gameplay::OperationEnum::EXFILTRATION ||
            operationType == spy::gameplay::OperationEnum::CAT_ACTION ||
            operationType == spy::gameplay::OperationEnum::JANITOR_ACTION) {
            return false;
        }

        return spy::gameplay::ActionValidator::validate(state, operation);

        return false;
    }
}