//
// Created by marco on 10.04.20.
//

#include <network/RoleEnum.hpp>
#include "Reconnect.hpp"

namespace spy::network::messages {

    Reconnect::Reconnect() : MessageContainer{MessageTypeEnum::RECONNECT, {}} {}

    Reconnect::Reconnect(const util::UUID &clientId, const util::UUID &sessionId) : MessageContainer{
            MessageTypeEnum::RECONNECT, clientId}, sessionId(sessionId) {}

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

    bool Reconnect::operator==(const Reconnect &rhs) const {
        return isEqual(rhs) &&
               sessionId == rhs.sessionId;
    }

    bool Reconnect::validate(RoleEnum playerRole) const {
        return playerRole != spy::network::RoleEnum::INVALID &&
               playerRole != spy::network::RoleEnum::SPECTATOR;
    }
}