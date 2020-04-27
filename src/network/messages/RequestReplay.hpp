//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_REQUESTREPLAY_HPP
#define LIBCOMMON_REQUESTREPLAY_HPP

#include <network/MessageContainer.hpp>
#include <network/RoleEnum.hpp>

namespace spy::network::messages {

    class RequestReplay : public MessageContainer {
        public:
            RequestReplay();

            explicit RequestReplay(const util::UUID &playerId);

            friend void to_json(nlohmann::json &j, const RequestReplay &r);

            friend void from_json(const nlohmann::json &j, RequestReplay &r);

            bool operator==(const RequestReplay &rhs) const;

            /**
             * validate message according role and replay availability
             * @param isReplayAvailable whether server support replay or not
             * @return true if message is valid
             *         false if message is not valid
             */
            [[nodiscard]] bool validate(RoleEnum playerRole, bool isReplayAvailable) const;
    };

}


#endif //LIBCOMMON_REQUESTREPLAY_HPP
