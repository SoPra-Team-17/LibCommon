//
// Created by jonas on 07.04.20.
//

#include "ConnectionError.hpp"

namespace spy::network::messages {
    void to_json(nlohmann::json &j, const ConnectionError &c) {
        MessageContainer::common_to_json(j, c);
        j["reason"] = c.reason;
    }

    void from_json(const nlohmann::json &j, ConnectionError &c) {
        MessageContainer::common_from_json(j, c);
        j.at("reason").get_to(c.reason);
    }

    ConnectionError::ConnectionError() :
            MessageContainer{MessageTypeEnum::CONNECTION_ERROR, {}} {}

    ConnectionError::ConnectionError(ErrorTypeEnum errorType) :
            MessageContainer{MessageTypeEnum::CONNECTION_ERROR, {}},
            reason{errorType} {}

    ErrorTypeEnum ConnectionError::getReason() const {
        return reason;
    }
}

