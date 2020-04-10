//
// Created by marco on 10.04.20.
//

#include "Replay.hpp"

namespace spy::network::messages {

    Replay::Replay() : MessageContainer{MessageTypeEnum::REPLAY, {}} {}

    Replay::Replay(const util::UUID &playerId,
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
                   std::vector<MessageContainer> messages)
            :
            MessageContainer{MessageTypeEnum::REPLAY, playerId},
            sessionId(sessionId),
            gameStart(std::move(gameStart)),
            gameEnd(std::move(gameEnd)),
            playerOneId(playerOneId),
            playerTwoId(playerTwoId),
            playerOneName(std::move(playerOneName)),
            playerTwoName(std::move(playerTwoName)),
            rounds(rounds),
            level(level),
            settings(settings),
            characterSettings(std::move(characterSettings)),
            messages(std::move(messages)){}

    void to_json(nlohmann::json &j, const Replay &r) {
        MessageContainer::common_to_json(j, r);
        j["sessionId"] = r.sessionId;
        j["gameStart"] = r.gameStart;
        j["gameEnd"] = r.gameEnd;
        j["playerOneId"] = r.playerOneId;
        j["playerTwoId"] = r.playerTwoId;
        j["playerOneName"] = r.playerOneName;
        j["playerTwoName"] = r.playerTwoName;
        j["rounds"] = r.rounds;
        j["level"] = r.level;
        j["settings"] = r.settings;
        //todo needs overlaod
        //j["characterSettings"] = r.characterSettings;
        j["messages"] = r.messages;
    }

    void from_json(const nlohmann::json &j, Replay &r) {
        MessageContainer::common_from_json(j, r);
        j.at("sessionId").get_to(r.sessionId);
        j.at("gameStart").get_to(r.gameStart);
        j.at("gameEnd").get_to(r.gameEnd);
        j.at("playerOneId").get_to(r.playerOneId);
        j.at("playerTwoId").get_to(r.playerTwoId);
        j.at("playerOneName").get_to(r.playerOneName);
        j.at("playerTwoName").get_to(r.playerTwoName);
        j.at("rounds").get_to(r.rounds);
        j.at("level").get_to(r.level);
        j.at("settings").get_to(r.settings);
        //todo needs overload
        //j.at("characterSettings").get_to(r.characterSettings);
        j.at("messages").get_to(r.messages);
    }

    const util::UUID &Replay::getSessionId() const {
        return sessionId;
    }

    const std::string &Replay::getGameStart() const {
        return gameStart;
    }

    const std::string &Replay::getGameEnd() const {
        return gameEnd;
    }

    const util::UUID &Replay::getPlayerOneId() const {
        return playerOneId;
    }

    const util::UUID &Replay::getPlayerTwoId() const {
        return playerTwoId;
    }

    const std::string &Replay::getPlayerOneName() const {
        return playerOneName;
    }

    const std::string &Replay::getPlayerTwoName() const {
        return playerTwoName;
    }

    int Replay::getRounds() const {
        return rounds;
    }

    const spy::scenario::Scenario &Replay::getLevel() const {
        return level;
    }

    const spy::MatchConfig &Replay::getSettings() const {
        return settings;
    }

    const spy::character::CharacterDescription &Replay::getCharacterSettings() const {
        return characterSettings;
    }

    auto Replay::getMessages() const -> const std::vector<MessageContainer> & {
        return messages;
    }


}