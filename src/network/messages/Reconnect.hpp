//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_RECONNECT_HPP
#define LIBCOMMON_RECONNECT_HPP

#include <network/MessageContainer.hpp>

namespace spy::network::messages {
    class Reconnect : public MessageContainer {
        public:
            Reconnect();

            Reconnect(const util::UUID &clientId, const util::UUID &sessionId);

            [[nodiscard]] const util::UUID &getSessionId() const;

            friend void to_json(nlohmann::json &j, const Reconnect &r);

            friend void from_json(const nlohmann::json &j, Reconnect &r);

            bool operator==(const Reconnect &rhs) const;

            /**
             * validate message according role
             * @param playerRole role of the player who sent the message
             * @return true if message is valid
             *         false if message is not valid
             */
            [[nodiscard]] bool validate(RoleEnum playerRole) const;

        private:
            util::UUID sessionId;
    };
}


#endif //LIBCOMMON_RECONNECT_HPP
