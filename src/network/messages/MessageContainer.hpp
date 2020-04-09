//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_MESSAGECONTAINER_HPP
#define LIBCOMMON_MESSAGECONTAINER_HPP

#include <util/UUID.hpp>
#include <network/messages/MessageTypeEnum.hpp>
#include <string>
#include <chrono>
#include <optional>
#include <nlohmann/json.hpp>
#include <util/OptionalSerialization.hpp>

namespace spy::network::messages {
    class MessageContainer {
        public:

            MessageContainer() = default;

            MessageContainer(MessageTypeEnum messageType, util::UUID playerId);

            friend void to_json(nlohmann::json &j, const MessageContainer &m);

            friend void from_json(const nlohmann::json &j, MessageContainer &m);

            /**
             * Create json with common message fields
             * @tparam T Message type deriving from MessageContainer
             */
            template<typename T>
            static void common_to_json(nlohmann::json &j, const T &message) {
                j["playerId"] = message.playerId;
                j["type"] = message.type;
                j["creationDate"] = message.creationDate;
                if (message.debugMessage.has_value()) {
                    j["debugMessage"] = message.debugMessage.value();
                }
            }

            /**
             * Fill common MessageContainer fields from json, to be used by classes deriving from MessageContainer.
             * @tparam T Message type deriving from MessageContainer
             */
            template<typename T>
            static void common_from_json(const nlohmann::json &j, T &message) {
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

        private:
            spy::util::UUID playerId;
            MessageTypeEnum type = MessageTypeEnum::INVALID;
            // TODO: std::chrono::system_clock::time_point creationDate;
            std::string creationDate;
            std::optional<std::string> debugMessage;

    };
}

#endif //LIBCOMMON_MESSAGECONTAINER_HPP
