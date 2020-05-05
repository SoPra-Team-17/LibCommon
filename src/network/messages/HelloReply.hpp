//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_HELLOREPLY_HPP
#define LIBCOMMON_HELLOREPLY_HPP

#include <util/UUID.hpp>
#include <datatypes/matchconfig/MatchConfig.hpp>
#include <datatypes/character/CharacterInformation.hpp>
#include <datatypes/scenario/Scenario.hpp>
#include <network/MessageContainer.hpp>

namespace spy::network::messages {

    class HelloReply : public MessageContainer {
        public:
            HelloReply();

            HelloReply(const util::UUID &clientId, const util::UUID &sessionId,
                       const scenario::Scenario &level, const MatchConfig &settings,
                       std::vector<character::CharacterInformation> characterSettings);

            [[nodiscard]] const util::UUID &getSessionId() const;

            [[nodiscard]] const scenario::Scenario &getLevel() const;

            [[nodiscard]] const MatchConfig &getSettings() const;

            [[nodiscard]] const std::vector<character::CharacterInformation> &getCharacterSettings() const;

            friend void to_json(nlohmann::json &j, const HelloReply &h);

            friend void from_json(const nlohmann::json &j, HelloReply &h);

            bool operator==(const HelloReply &rhs) const;

        private:
            util::UUID sessionId;
            scenario::Scenario level;
            MatchConfig settings;
            std::vector<character::CharacterInformation> characterSettings;
    };
}

#endif //LIBCOMMON_HELLOREPLY_HPP
