//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_REQUESTGAMEPAUSE_HPP
#define LIBCOMMON_REQUESTGAMEPAUSE_HPP

#include <network/MessageContainer.hpp>

namespace spy::network::messages {

    class RequestGamePause : public MessageContainer {
        public:
            RequestGamePause();

            RequestGamePause(const util::UUID &playerId, bool gamePause);

            [[nodiscard]] bool getGamePause() const;

            friend void to_json(nlohmann::json &j, const RequestGamePause &r);

            friend void from_json(const nlohmann::json &j, RequestGamePause &r);

        private:
            bool gamePause;
    };

}


#endif //LIBCOMMON_REQUESTGAMEPAUSE_HPP
