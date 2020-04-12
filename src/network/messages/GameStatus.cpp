//
// Created by marco on 10.04.20.
//

#include "GameStatus.hpp"

namespace spy::network::messages {

    GameStatus::GameStatus() : MessageContainer{MessageTypeEnum::GAME_STATUS, {}} {}

    GameStatus::GameStatus(const util::UUID &playerId, const util::UUID &activeCharacterId,
                           const std::vector<spy::gameplay::Operation> &operations, const spy::gameplay::State &state,
                           bool isGameOver) :
            MessageContainer{MessageTypeEnum::GAME_STATUS, playerId},
            activeCharacterId(activeCharacterId),
            operations(operations),
            state(state),
            isGameOver(isGameOver) {}

    void to_json(nlohmann::json &j, const GameStatus &g) {
        MessageContainer::common_to_json(j, g);
        j["activeCharacter"] = g.activeCharacterId;
        j["operations"] = g.operations;
        j["state"] = g.state;
        j["isGameOver"] = g.isGameOver;
    }

    void from_json(const nlohmann::json &j, GameStatus &g) {
        MessageContainer::common_from_json(j, g);
        j.at("activeCharacter").get_to(g.activeCharacterId);
        j.at("operations").get_to(g.operations);
        j.at("state").get_to(g.state);
        j.at("isGameOver").get_to(g.isGameOver);
    }

    const util::UUID &GameStatus::getActiveCharacterId() const {
        return activeCharacterId;
    }

    const std::vector<spy::gameplay::Operation> &GameStatus::getOperations() const {
        return operations;
    }

    const spy::gameplay::State &GameStatus::getState() const {
        return state;
    }

    bool GameStatus::getIsGameOver() const {
        return isGameOver;
    }

}