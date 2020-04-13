//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_GAMESTARTED_HPP
#define LIBCOMMON_GAMESTARTED_HPP

#include <network/MessageContainer.hpp>

namespace spy::network::messages {
    class GameStarted : public MessageContainer {
        public:
            GameStarted();

            GameStarted(const util::UUID &playerId, const util::UUID &playerOneId, const util::UUID &playerTwoId, std::string playerOneName,
                        std::string playerTwoName, const util::UUID &sessionId);

            [[nodiscard]] const util::UUID &getPlayerOneId() const;

            [[nodiscard]] const util::UUID &getPlayerTwoId() const;

            [[nodiscard]] const std::string &getPlayerOneName() const;

            [[nodiscard]] const std::string &getPlayerTwoName() const;

            [[nodiscard]] const util::UUID &getSessionId() const;

            friend void to_json(nlohmann::json &j, const GameStarted &g);

            friend void from_json(const nlohmann::json &j, GameStarted &g);

            bool operator==(const GameStarted &rhs) const;

        private:
            util::UUID playerOneId;
            util::UUID playerTwoId;
            std::string playerOneName;
            std::string playerTwoName;
            util::UUID sessionId;
    };
}


#endif //LIBCOMMON_GAMESTARTED_HPP
