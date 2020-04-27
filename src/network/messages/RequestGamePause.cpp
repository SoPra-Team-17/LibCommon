//
// Created by marco on 10.04.20.
//

#include "RequestGamePause.hpp"

namespace spy::network::messages {

    RequestGamePause::RequestGamePause() : MessageContainer{MessageTypeEnum::REQUEST_GAME_PAUSE, {}} {}

    RequestGamePause::RequestGamePause(const util::UUID &playerId, bool gamePause) : MessageContainer{
            MessageTypeEnum::REQUEST_GAME_PAUSE, playerId}, gamePause(gamePause) {}


    void to_json(nlohmann::json &j, const RequestGamePause &r) {
        MessageContainer::common_to_json(j, r);
        j["gamePause"] = r.gamePause;
    }

    void from_json(const nlohmann::json &j, RequestGamePause &r) {
        MessageContainer::common_from_json(j, r);
        j.at("gamePause").get_to(r.gamePause);
    }

    bool RequestGamePause::getGamePause() const {
        return gamePause;
    }

    bool RequestGamePause::operator==(const RequestGamePause &rhs) const {
        return isEqual(rhs) &&
               gamePause == rhs.gamePause;
    }

    bool RequestGamePause::validate(RoleEnum playerRole, bool isGamePaused, bool isServerEnforced) const {
        return playerRole == RoleEnum::PLAYER && !isServerEnforced && gamePause == !isGamePaused;
    }
}