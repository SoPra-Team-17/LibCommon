//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_GAMESTATUS_HPP
#define LIBCOMMON_GAMESTATUS_HPP

#include <datatypes/gameplay/BaseOperation.hpp>
#include <datatypes/gameplay/State.hpp>
#include <network/MessageContainer.hpp>

namespace spy::network::messages {

    class GameStatus : public MessageContainer {
        public:
            GameStatus();

            GameStatus(const util::UUID &clientId, const util::UUID &activeCharacterId,
                       std::vector<std::shared_ptr<spy::gameplay::BaseOperation>> operations,
                       const spy::gameplay::State &state,
                       bool isGameOver);

            [[nodiscard]] const util::UUID &getActiveCharacterId() const;

            [[nodiscard]] const std::vector<std::shared_ptr<spy::gameplay::BaseOperation>> &getOperations() const;

            [[nodiscard]] const spy::gameplay::State &getState() const;

            [[nodiscard]] bool getIsGameOver() const;

            friend void to_json(nlohmann::json &j, const GameStatus &g);

            friend void from_json(const nlohmann::json &j, GameStatus &g);

            bool operator==(const GameStatus &rhs) const;

        private:
            util::UUID activeCharacterId;
            std::vector<std::shared_ptr<spy::gameplay::BaseOperation>> operations;
            spy::gameplay::State state;
            bool isGameOver;

    };
}


#endif //LIBCOMMON_GAMESTATUS_HPP
