//
// Created by jonas on 07.04.20.
//

#include "GameLeft.hpp"

namespace spy::network::messages {
    void to_json(nlohmann::json &j, const GameLeft &g) {
        MessageContainer::common_to_json(j, g);
        j["leftUserId"] = g.leftUserId;
    }

    void from_json(const nlohmann::json &j, GameLeft &g) {
        MessageContainer::common_from_json(j, g);
        j.at("leftUserId").get_to(g.leftUserId);
    }

    GameLeft::GameLeft() : MessageContainer{MessageTypeEnum::GAME_LEFT, {}} {}

    GameLeft::GameLeft(util::UUID clientId, util::UUID leftUserId) :
            MessageContainer{MessageTypeEnum::GAME_LEFT, clientId},
            leftUserId{leftUserId} {}

    bool GameLeft::operator==(const GameLeft &rhs) const {
        return isEqual(rhs) &&
               leftUserId == rhs.leftUserId;
    }

    const util::UUID &GameLeft::getLeftUserId() const {
        return leftUserId;
    }
}