//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_GAMEPAUSE_HPP
#define LIBCOMMON_GAMEPAUSE_HPP

#include <network/messages/MessageContainer.hpp>

namespace spy::network::messages {
    class GamePause : public MessageContainer {
        public:
            GamePause() = default;

            explicit GamePause(bool pause);

            [[nodiscard]] bool isGamePause() const;

            friend void to_json(nlohmann::json &j, const GamePause &g);

            friend void from_json(const nlohmann::json &j, GamePause &g);

        private:
            bool gamePause = false;
    };
}

#endif //LIBCOMMON_GAMEPAUSE_HPP
