//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_GAMEPAUSE_HPP
#define LIBCOMMON_GAMEPAUSE_HPP

#include <network/MessageContainer.hpp>

namespace spy::network::messages {
    class GamePause : public MessageContainer {
        public:
            GamePause();

            GamePause(util::UUID playerId, bool pause, bool serverEnforced);

            [[nodiscard]] bool isGamePause() const;

            [[nodiscard]] bool isServerEnforced() const;

            friend void to_json(nlohmann::json &j, const GamePause &g);

            friend void from_json(const nlohmann::json &j, GamePause &g);

        private:
            bool gamePause = false;
            bool serverEnforced = false;
    };
}

#endif //LIBCOMMON_GAMEPAUSE_HPP
