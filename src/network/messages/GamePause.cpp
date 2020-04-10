//
// Created by jonas on 07.04.20.
//

#include "GamePause.hpp"

namespace spy::network::messages {

    GamePause::GamePause() : MessageContainer{MessageTypeEnum::GAME_PAUSE, {}} {}

    GamePause::GamePause(util::UUID playerId, bool pause) :
            MessageContainer{MessageTypeEnum::GAME_PAUSE, playerId},
            gamePause{pause} {}

    void to_json(nlohmann::json &j, const GamePause &g) {
        MessageContainer::common_to_json(j, g);
        j["gamePause"] = g.gamePause;
    }

    void from_json(const nlohmann::json &j, GamePause &g) {
        MessageContainer::common_from_json(j, g);
        j.at("gamePause").get_to(g.gamePause);
    }

    bool GamePause::isGamePause() const {
        return gamePause;
    }
}