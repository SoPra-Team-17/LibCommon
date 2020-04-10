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

namespace spy::network {
    class MessageContainer {
        public:

            MessageContainer() = default;

            MessageContainer(messages::MessageTypeEnum messageType, util::UUID playerId);

            friend void to_json(nlohmann::json &j, const MessageContainer &m);

            friend void from_json(const nlohmann::json &j, MessageContainer &m);

            /**
             * Create json with common message fields
             */
            static void common_to_json(nlohmann::json &j, const MessageContainer &message);

            /**
             * Fill common MessageContainer fields from json, to be used by classes deriving from MessageContainer.
             */
            static void common_from_json(const nlohmann::json &j, MessageContainer &message);

        private:
            spy::util::UUID playerId;
            messages::MessageTypeEnum type = messages::MessageTypeEnum::INVALID;
            // TODO: std::chrono::system_clock::time_point creationDate;
            std::string creationDate;
            std::optional<std::string> debugMessage;

    };
}

#endif //LIBCOMMON_MESSAGECONTAINER_HPP
