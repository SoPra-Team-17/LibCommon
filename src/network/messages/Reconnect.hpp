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

        private:
            util::UUID sessionId;
    };
}


#endif //LIBCOMMON_RECONNECT_HPP
