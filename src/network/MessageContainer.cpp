//
// Created by jonas on 07.04.20.
//

#include "MessageContainer.hpp"
#include <util/OptionalSerialization.hpp>
#include <ctime>
#include <iostream>

namespace spy::network {
    void to_json(nlohmann::json &j, const MessageContainer &m) {
        MessageContainer::common_to_json(j, m);
    }

    void from_json(const nlohmann::json &j, MessageContainer &m) {
        MessageContainer::common_from_json(j, m);
    }

    MessageContainer::MessageContainer(messages::MessageTypeEnum messageType, util::UUID clientId) :
            clientId(clientId),
            type(messageType) {
        setenv("TZ", "Africa/Malabo", 1); // UTC+1 the whole year
        std::time_t rawtime = std::time(nullptr);
        struct std::tm creationDateTM;
        localtime_r(&rawtime, &creationDateTM);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S", &creationDateTM);
        creationDate = std::string(buffer);
    }

    void MessageContainer::common_to_json(nlohmann::json &j, const MessageContainer &message) {
        j["clientId"] = message.clientId;
        j["type"] = message.type;
        j["creationDate"] = message.creationDate;
        if (message.debugMessage.has_value()) {
            j["debugMessage"] = message.debugMessage.value();
        }
    }

    void MessageContainer::common_from_json(const nlohmann::json &j, MessageContainer &message) {
        j.at("clientId").get_to(message.clientId);
        j.at("type").get_to(message.type);
        j.at("creationDate").get_to(message.creationDate);
        if (j.find("debugMessage") != j.end()) {
            // debugMessage present
            j.at("debugMessage").get_to(message.debugMessage);
        } else {
            message.debugMessage = std::nullopt;
        }
    }

    const util::UUID &MessageContainer::getclientId() const {
        return clientId;
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
        return std::tie(clientId, type, creationDate, debugMessage) ==
               std::tie(rhs.clientId, rhs.type, rhs.creationDate, rhs.debugMessage);
    }
}
