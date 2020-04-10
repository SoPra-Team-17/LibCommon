//
// Created by jonas on 07.04.20.
//

#include "HelloReply.hpp"

#include <utility>

namespace spy::network::messages {

    HelloReply::HelloReply() : MessageContainer{MessageTypeEnum::HELLO_REPLY, {}} {}

    HelloReply::HelloReply(const util::UUID &playerId, const util::UUID &sessionId,
                           const scenario::Scenario &level, const MatchConfig &settings,
                           std::vector<character::CharacterInformation> characterSettings) :
            MessageContainer{MessageTypeEnum::HELLO_REPLY, playerId},
            sessionId{sessionId},
            level{level},
            settings{settings},
            characterSettings{std::move(characterSettings)} {}


    void to_json(nlohmann::json &j, const HelloReply &h) {
        MessageContainer::common_to_json(j, h);
        j["sessionId"] = h.sessionId;
        j["level"] = h.level;
        j["settings"] = h.settings;
        j["characterSettings"] = h.characterSettings;
    }

    void from_json(const nlohmann::json &j, HelloReply &h) {
        MessageContainer::common_from_json(j, h);
        j.at("sessionId").get_to(h.sessionId);
        j.at("level").get_to(h.level);
        j.at("settings").get_to(h.settings);
        j.at("characterSettings").get_to(h.characterSettings);
    }
}