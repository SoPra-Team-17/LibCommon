//
// Created by marco on 10.04.20.
//

#include "RequestGameOperation.hpp"

namespace spy::network::messages {
    RequestGameOperation::RequestGameOperation() : MessageContainer{MessageTypeEnum::REQUEST_GAME_OPERATION, {}} {}

    RequestGameOperation::RequestGameOperation(const util::UUID &playerId, const util::UUID &characterId)
            : MessageContainer{MessageTypeEnum::REQUEST_GAME_OPERATION, playerId}, characterId(characterId) {}


    void to_json(nlohmann::json &j, const RequestGameOperation &r) {
        MessageContainer::common_to_json(j, r);
        j["characterId"] = r.characterId;
    }

    void from_json(const nlohmann::json &j, RequestGameOperation &r) {
        MessageContainer::common_from_json(j, r);
        j.at("characterId").get_to(r.characterId);
    }

    const util::UUID &RequestGameOperation::getCharacterId() const {
        return characterId;
    }
}