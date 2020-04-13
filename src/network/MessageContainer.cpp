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
        struct tm creationDateTM = *gmtime(&rawtime);
        creationDateTM.tm_hour = (creationDateTM.tm_hour + 1) % 24;
        char buffer[20];
        strptime(buffer, "%d.%m.%Y %H:%M:%S", &creationDateTM);
        creationDate = std::string(buffer);
    }

    void MessageContainer::common_to_json(nlohmann::json &j, const MessageContainer &message) {
        j["playerId"] = message.playerId;
        j["type"] = message.type;
        j["creationDate"] = message.creationDate;
        if (message.debugMessage.has_value()) {
            j["debugMessage"] = message.debugMessage.value();
        }
    }

    void MessageContainer::common_from_json(const nlohmann::json &j, MessageContainer &message) {
        j.at("playerId").get_to(message.playerId);
        j.at("type").get_to(message.type);
        j.at("creationDate").get_to(message.creationDate);
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

    const std::string &MessageContainer::getCreationDate() const {
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