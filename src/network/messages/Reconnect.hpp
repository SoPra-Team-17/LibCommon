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

            Reconnect(const util::UUID &playerId, const util::UUID &sessionId);

            [[nodiscard]] const util::UUID &getSessionId() const;

            friend void to_json(nlohmann::json &j, const Reconnect &r);

            friend void from_json(const nlohmann::json &j, Reconnect &r);

            bool operator==(const Reconnect &rhs) const;

            /**
             * validate message according role and if player is known
             * @param playerRole role of the player who sent the message
             * @param isPlayerKnown whether playerId of message is known or not
             * @return true if message is valid
             *         false if message is not valid
             */
            [[nodiscard]] bool validate(const RoleEnum &playerRole, bool isPlayerKnown) const;

        private:
            util::UUID sessionId;
    };
}


#endif //LIBCOMMON_RECONNECT_HPP
