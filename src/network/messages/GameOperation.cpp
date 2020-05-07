/**
 * @file   GameOperation.cpp
 * @author Jonas
 * @date   07.04.2020 (creation)
 * @brief  Implementation of a game operation message.
 */

#include <utility>
#include <iostream>
#include "util/OperationSerialization.hpp"
#include "GameOperation.hpp"
#include "gameLogic/validation/ActionValidator.hpp"


namespace spy::network::messages {
    GameOperation::GameOperation() : MessageContainer{MessageTypeEnum::GAME_OPERATION, {}} {}

    GameOperation::GameOperation(spy::util::UUID clientId, std::shared_ptr<gameplay::BaseOperation> operation) :
            MessageContainer{MessageTypeEnum::GAME_OPERATION, clientId},
            operation{std::move(operation)} {}

    void to_json(nlohmann::json &j, const GameOperation &g) {
        MessageContainer::common_to_json(j, g);
        j["operation"] = g.operation;
    }

    void from_json(const nlohmann::json &j, GameOperation &g) {
        MessageContainer::common_from_json(j, g);
        j.at("operation").get_to(g.operation);
    }

    std::shared_ptr<const gameplay::BaseOperation> GameOperation::getOperation() const {
        return operation;
    }

    bool GameOperation::operator==(const GameOperation &rhs) const {
        return isEqual(rhs) && (operation->operator==(*(rhs.operation)));
    }

    bool GameOperation::validate(RoleEnum playerRole, const spy::gameplay::State &state, util::UUID activeCharacter,
                                 const MatchConfig &config) const {
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

        if (std::dynamic_pointer_cast<const gameplay::CharacterOperation>(operation)->getCharacterId() !=
            activeCharacter) {
            return false;
        }

        return spy::gameplay::ActionValidator::validate(state, operation, config);
    }

    std::ostream &operator<<(std::ostream &os, const GameOperation &metaInformation) {
        nlohmann::json j = metaInformation;
        return os << j;
    }
}