//
// Created by marco on 10.04.20.
//

#include "GameStarted.hpp"

#include <utility>


namespace spy::network::messages {


    GameStarted::GameStarted() : MessageContainer{MessageTypeEnum::GAME_STARTED, {}} {}

    GameStarted::GameStarted(const util::UUID &clientId, const util::UUID &playerOneId, const util::UUID &playerTwoId,
                             std::string playerOneName, std::string playerTwoName,
                             const util::UUID &sessionId) : MessageContainer{MessageTypeEnum::GAME_STARTED, clientId},
                                                            playerOneId(playerOneId), playerTwoId(playerTwoId),
                                                            playerOneName(std::move(playerOneName)),
                                                            playerTwoName(std::move(playerTwoName)),
                                                            sessionId(sessionId) {}

    void to_json(nlohmann::json &j, const GameStarted &g) {
        MessageContainer::common_to_json(j, g);
        j["playerOneId"] = g.playerOneId;
        j["playerTwoId"] = g.playerTwoId;
        j["playerOneName"] = g.playerOneName;
        j["playerTwoName"] = g.playerTwoName;
        j["sessionId"] = g.sessionId;
    }

    void from_json(const nlohmann::json &j, GameStarted &g) {
        MessageContainer::common_from_json(j, g);
        j.at("playerOneId").get_to(g.playerOneId);
        j.at("playerTwoId").get_to(g.playerTwoId);
        j.at("playerOneName").get_to(g.playerOneName);
        j.at("playerTwoName").get_to(g.playerTwoName);
        j.at("sessionId").get_to(g.sessionId);
    }


    const util::UUID &GameStarted::getPlayerOneId() const {
        return playerOneId;
    }

    const util::UUID &GameStarted::getPlayerTwoId() const {
        return playerTwoId;
    }

    const std::string &GameStarted::getPlayerOneName() const {
        return playerOneName;
    }

    const std::string &GameStarted::getPlayerTwoName() const {
        return playerTwoName;
    }

    const spy::util::UUID &GameStarted::getSessionId() const {
        return sessionId;
    }

    bool GameStarted::operator==(const GameStarted &rhs) const {
        return isEqual(rhs) &&
               playerOneId == rhs.playerOneId &&
               playerTwoId == rhs.playerTwoId &&
               playerOneName == rhs.playerOneName &&
               playerTwoName == rhs.playerTwoName &&
               sessionId == rhs.sessionId;
    }


}