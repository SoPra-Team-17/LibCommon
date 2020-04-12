//
// Created by jonas on 07.04.20.
//

#include "GameLeave.hpp"

namespace spy::network::messages {
    void to_json(nlohmann::json &j, const GameLeave &g) {
        MessageContainer::common_to_json(j, g);
    }

    void from_json(const nlohmann::json &j, GameLeave &g) {
        MessageContainer::common_from_json(j, g);
    }

    GameLeave::GameLeave() : MessageContainer{MessageTypeEnum::GAME_LEAVE, {}} {}

    GameLeave::GameLeave(util::UUID playerId) : MessageContainer{MessageTypeEnum::GAME_LEAVE, playerId} {}
}