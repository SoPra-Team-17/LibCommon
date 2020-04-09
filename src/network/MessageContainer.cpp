//
// Created by jonas on 07.04.20.
//

#include "MessageContainer.hpp"
#include <util/OptionalSerialization.hpp>

namespace spy::network {
    void to_json(nlohmann::json &j, const MessageContainer &m) {
        MessageContainer::common_to_json(j, m);
    }

    void from_json(const nlohmann::json &j, MessageContainer &m) {
        MessageContainer::common_from_json(j, m);
    }

    // TODO initialize creationdate
    MessageContainer::MessageContainer(messages::MessageTypeEnum messageType, util::UUID playerId) :
            playerId(playerId),
            type(messageType) {}
}