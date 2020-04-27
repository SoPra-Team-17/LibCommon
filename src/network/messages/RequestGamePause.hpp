//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_REQUESTGAMEPAUSE_HPP
#define LIBCOMMON_REQUESTGAMEPAUSE_HPP

#include <network/MessageContainer.hpp>
#include <network/RoleEnum.hpp>

namespace spy::network::messages {

    class RequestGamePause : public MessageContainer {
        public:
            RequestGamePause();

            RequestGamePause(const util::UUID &playerId, bool gamePause);

            [[nodiscard]] bool getGamePause() const;

            friend void to_json(nlohmann::json &j, const RequestGamePause &r);

            friend void from_json(const nlohmann::json &j, RequestGamePause &r);

            bool operator==(const RequestGamePause &rhs) const;

            /**
             * validate message according role and if game is currently paused and if paused by server
             * @param playerRole role of the player who sent the message
             * @param isGamePaused whether game is paused by player
             * @param isServerEnforced whether game is paused by server
             * @return true if message is valid
             *         false if message is not valid
             */
            [[nodiscard]] bool validate(RoleEnum playerRole, bool isGamePaused, bool isServerEnforced) const;

        private:
            bool gamePause;
    };

}


#endif //LIBCOMMON_REQUESTGAMEPAUSE_HPP
