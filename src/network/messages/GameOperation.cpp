//
// Created by jonas on 07.04.20.
//

#include "GameOperation.hpp"

namespace spy::network::messages {
    GameOperation::GameOperation() : MessageContainer{MessageTypeEnum::GAME_OPERATION, {}} {}

    GameOperation::GameOperation(spy::util::UUID playerId, spy::gameplay::Operation operation) :
            MessageContainer{MessageTypeEnum::GAME_OPERATION, playerId},
            operation{operation} {}

    void to_json(nlohmann::json &j, const GameOperation &g) {
        MessageContainer::common_to_json(j, g);
        j["operation"] = g.operation;
    }

    void from_json(const nlohmann::json &j, GameOperation &g) {
        MessageContainer::common_from_json(j, g);
        j.at("operation").get_to(g.operation);
    }
}