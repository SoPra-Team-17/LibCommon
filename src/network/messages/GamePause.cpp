//
// Created by jonas on 07.04.20.
//

#include "GamePause.hpp"

namespace spy::network::messages {

    GamePause::GamePause() : MessageContainer{MessageTypeEnum::GAME_PAUSE, {}} {}

    GamePause::GamePause(util::UUID playerId, bool pause, bool serverEnforced) :
            MessageContainer{MessageTypeEnum::GAME_PAUSE, playerId},
            gamePause{pause},
            serverEnforced{serverEnforced} {}

    void to_json(nlohmann::json &j, const GamePause &g) {
        MessageContainer::common_to_json(j, g);
        j["gamePause"] = g.gamePause;
        j["serverEnforced"] = g.serverEnforced;
    }

    void from_json(const nlohmann::json &j, GamePause &g) {
        MessageContainer::common_from_json(j, g);
        j.at("gamePause").get_to(g.gamePause);
        j.at("serverEnforced").get_to(g.serverEnforced);
    }

    bool GamePause::isGamePause() const {
        return gamePause;
    }

    bool GamePause::isServerEnforced() const {
        return serverEnforced;
    }
}