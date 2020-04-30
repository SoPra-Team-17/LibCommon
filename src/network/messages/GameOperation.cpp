//
// Created by jonas on 07.04.20.
//

#include <datatypes/validation/ActionValidator.hpp>
#include <utility>
#include <datatypes/gameplay/OperationJson.hpp>
#include "GameOperation.hpp"
#include <iostream>
#include <openssl/ossl_typ.h>

namespace spy::network::messages {
    GameOperation::GameOperation() : MessageContainer{MessageTypeEnum::GAME_OPERATION, {}} {}

    GameOperation::GameOperation(spy::util::UUID playerId, std::shared_ptr<gameplay::BaseOperation> operation) :
            MessageContainer{MessageTypeEnum::GAME_OPERATION, playerId},
            operation{std::move(operation)} {}

    void to_json(nlohmann::json &j, const GameOperation &g) {
        MessageContainer::common_to_json(j, g);
        j["operation"] = gameplay::OperationJson::toJson(g.operation);
    }

    void from_json(const nlohmann::json &j, GameOperation &g) {
        MessageContainer::common_from_json(j, g);
        g.operation = gameplay::OperationJson::fromJson(j.at("operation"));
    }

    const std::shared_ptr<gameplay::BaseOperation> &GameOperation::getOperation() const {
        return operation;
    }

    bool GameOperation::operator==(const GameOperation &rhs) const {
        auto r = isEqual(rhs) && (operation->operator==(*(rhs.operation)));
        std::cout << "Compared GameOperation: " << r << std::endl;
        return r;
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
    }

    std::ostream &operator<<(std::ostream &os, const GameOperation &metaInformation) {
        nlohmann::json j = metaInformation;
        return os << j;
    }
}