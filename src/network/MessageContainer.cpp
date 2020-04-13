//
// Created by jonas on 07.04.20.
//

#include "MessageContainer.hpp"
#include <util/OptionalSerialization.hpp>
#include <time.h>

namespace spy::network {
    void to_json(nlohmann::json &j, const MessageContainer &m) {
        MessageContainer::common_to_json(j, m);
    }

    void from_json(const nlohmann::json &j, MessageContainer &m) {
        MessageContainer::common_from_json(j, m);
    }

    MessageContainer::MessageContainer(messages::MessageTypeEnum messageType, util::UUID playerId) :
            playerId(playerId),
            type(messageType) {
        time_t rawtime = time(nullptr);
        creationDate = *gmtime(&rawtime);
        creationDate.tm_hour = (creationDate.tm_hour + 1) % 24;
    }

    void MessageContainer::common_to_json(nlohmann::json &j, const MessageContainer &message) {
        j["playerId"] = message.playerId;
        j["type"] = message.type;
        char buffer[20];
        strftime(buffer, 20, "%d.%m.%Y %H:%M:%S", &message.creationDate);
        j["creationDate"] = std::string(buffer);
        if (message.debugMessage.has_value()) {
            j["debugMessage"] = message.debugMessage.value();
        }
    }

    void MessageContainer::common_from_json(const nlohmann::json &j, MessageContainer &message) {
        j.at("playerId").get_to(message.playerId);
        j.at("type").get_to(message.type);
        char buffer[20];
        j.at("creationDate").get_to(buffer);
        strptime(buffer, "%d.%m.%Y %H:%M:%S", &message.creationDate);
        if (j.find("debugMessage") != j.end()) {
            // debugMessage present
            j.at("debugMessage").get_to(message.debugMessage);
        } else {
            message.debugMessage = std::nullopt;
        }
    }

    const util::UUID &MessageContainer::getPlayerId() const {
        return playerId;
    }

    messages::MessageTypeEnum MessageContainer::getType() const {
        return type;
    }

    const struct tm &MessageContainer::getCreationDate() const {
        return creationDate;
    }

    const std::optional<std::string> &MessageContainer::getDebugMessage() const {
        return debugMessage;
    }

    void MessageContainer::setDebugMessage(const std::optional<std::string> &newDebugMessage) {
        MessageContainer::debugMessage = newDebugMessage;
    }

    bool MessageContainer::isEqual(const MessageContainer &rhs) const {
        return std::tie(playerId, type, creationDate, debugMessage) ==
               std::tie(rhs.playerId, rhs.type, rhs.creationDate, rhs.debugMessage);
    }
}