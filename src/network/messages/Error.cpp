//
// Created by jonas on 10.04.20.
//

#include "Error.hpp"

namespace spy::network::messages {
    ErrorTypeEnum Error::getReason() const {
        return reason;
    }

    Error::Error() : MessageContainer{MessageTypeEnum::ERROR, {}} {}

    Error::Error(util::UUID clientId, ErrorTypeEnum reason) :
            MessageContainer{MessageTypeEnum::ERROR, clientId},
            reason{reason} {}


    void to_json(nlohmann::json &j, const Error &e) {
        MessageContainer::common_to_json(j, e);
        j["reason"] = e.reason;
    }

    void from_json(const nlohmann::json &j, Error &e) {
        MessageContainer::common_from_json(j, e);
        j.at("reason").get_to(e.reason);
    }

    bool Error::operator==(const Error &rhs) const {
        return isEqual(rhs) &&
               reason == rhs.reason;
    }
}