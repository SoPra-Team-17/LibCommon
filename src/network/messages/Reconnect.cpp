//
// Created by marco on 10.04.20.
//

#include "Reconnect.hpp"

namespace spy::network::messages {

    Reconnect::Reconnect() : MessageContainer{MessageTypeEnum::RECONNECT, {}} {}

    Reconnect::Reconnect(const util::UUID &playerId, const util::UUID &sessionId) : MessageContainer{
            MessageTypeEnum::RECONNECT, playerId}, sessionId(sessionId) {}

    void to_json(nlohmann::json &j, const Reconnect &r) {
        MessageContainer::common_to_json(j, r);
        j["sessionId"] = r.sessionId;
    }

    void from_json(const nlohmann::json &j, Reconnect &r) {
        MessageContainer::common_from_json(j, r);
        j.at("sessionId").get_to(r.sessionId);
    }

    const util::UUID &Reconnect::getSessionId() const {
        return sessionId;
    }
}