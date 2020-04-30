//
// Created by marco on 10.04.20.
//

#include "GameStatus.hpp"
#include <gameplay/OperationJson.hpp>
#include <utility>
#include <iostream>

namespace spy::network::messages {

    GameStatus::GameStatus() : MessageContainer{MessageTypeEnum::GAME_STATUS, {}} {}

    GameStatus::GameStatus(const util::UUID &playerId, const util::UUID &activeCharacterId,
                           std::vector<std::shared_ptr<spy::gameplay::BaseOperation>> operations,
                           const spy::gameplay::State &state,
                           bool isGameOver) :
            MessageContainer{MessageTypeEnum::GAME_STATUS, playerId},
            activeCharacterId(activeCharacterId),
            operations(std::move(operations)),
            state(state),
            isGameOver(isGameOver) {}

    void to_json(nlohmann::json &j, const GameStatus &g) {
        MessageContainer::common_to_json(j, g);
        j["activeCharacter"] = g.activeCharacterId;
        j["operations"] = nlohmann::json::array();
        for (const auto &op: g.operations) {
            j["operations"].push_back(gameplay::OperationJson::toJson(op));
        }
        j["state"] = g.state;
        j["isGameOver"] = g.isGameOver;
    }

    void from_json(const nlohmann::json &j, GameStatus &g) {
        MessageContainer::common_from_json(j, g);
        j.at("activeCharacter").get_to(g.activeCharacterId);
        for (const auto &op: j.at("operations")) {
            g.operations.push_back(gameplay::OperationJson::fromJson(op));
        }
        j.at("state").get_to(g.state);
        j.at("isGameOver").get_to(g.isGameOver);
    }

    const util::UUID &GameStatus::getActiveCharacterId() const {
        return activeCharacterId;
    }

    const std::vector<std::shared_ptr<spy::gameplay::BaseOperation>> &GameStatus::getOperations() const {
        return operations;
    }

    const spy::gameplay::State &GameStatus::getState() const {
        return state;
    }

    bool GameStatus::getIsGameOver() const {
        return isGameOver;
    }

    bool GameStatus::operator==(const GameStatus &rhs) const {
        std::cout << "Comparing GameStatus" << std::endl;
        if (operations.size() != rhs.operations.size()) {
            return false;
        }
        for (unsigned int i = 0; i < operations.size(); i++) {
            if (*operations.at(i) != *rhs.operations.at(i)) {
                return false;
            }
        }
        return isEqual(rhs) &&
               activeCharacterId == rhs.activeCharacterId &&
               state == rhs.state &&
               isGameOver == rhs.isGameOver;
    }

}