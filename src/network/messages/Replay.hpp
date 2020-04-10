//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_REPLAY_HPP
#define LIBCOMMON_REPLAY_HPP

#include <network/MessageContainer.hpp>
#include <datatypes/scenario/Scenario.hpp>
#include <datatypes/matchconfig/MatchConfig.hpp>
#include <datatypes/character/CharacterDescription.hpp>

namespace spy::network::messages {

    class Replay : public MessageContainer {
        public:

            Replay();

            // TODO: std::chrono::system_clock::time_point creationDate;
            Replay(
                    const util::UUID &playerId,
                    const util::UUID &sessionId,
                    std::string gameStart,
                    std::string gameEnd,
                    const util::UUID &playerOneId,
                    const util::UUID &playerTwoId,
                    std::string playerOneName,
                    std::string playerTwoName,
                    int rounds,
                    const spy::scenario::Scenario &level,
                    const spy::MatchConfig &settings,
                    spy::character::CharacterDescription characterSettings,
                    std::vector<MessageContainer> messages
            );


            [[nodiscard]] const util::UUID &getSessionId() const;

            [[nodiscard]] const std::string &getGameStart() const;

            [[nodiscard]] const std::string &getGameEnd() const;

            [[nodiscard]] const util::UUID &getPlayerOneId() const;

            [[nodiscard]] const util::UUID &getPlayerTwoId() const;

            [[nodiscard]] const std::string &getPlayerOneName() const;

            [[nodiscard]] const std::string &getPlayerTwoName() const;

            [[nodiscard]] int getRounds() const;

            [[nodiscard]] const spy::scenario::Scenario &getLevel() const;

            [[nodiscard]] const spy::MatchConfig &getSettings() const;

            [[nodiscard]] const spy::character::CharacterDescription &getCharacterSettings() const;

            [[nodiscard]] auto getMessages() const -> const std::vector<MessageContainer> &;

            friend void to_json(nlohmann::json &j, const Replay &r);

            friend void from_json(const nlohmann::json &j, Replay &r);

        private:
            util::UUID sessionId;
            std::string gameStart, gameEnd;
            util::UUID playerOneId, playerTwoId;
            std::string playerOneName, playerTwoName;
            int rounds;
            spy::scenario::Scenario level;
            spy::MatchConfig settings;
            spy::character::CharacterDescription characterSettings;
            std::vector<MessageContainer> messages;
    };

}

#endif //LIBCOMMON_REPLAY_HPP
