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

            HelloReply(const util::UUID &playerId, const util::UUID &sessionId,
                       const scenario::Scenario &level, const MatchConfig &settings,
                       std::vector<character::CharacterInformation> characterSettings);

            friend void to_json(nlohmann::json &j, const HelloReply &h);

            friend void from_json(const nlohmann::json &j, HelloReply &h);


        private:
            util::UUID sessionId;
            scenario::Scenario level;
            MatchConfig settings;
            std::vector<character::CharacterInformation> characterSettings;
    };
}

#endif //LIBCOMMON_HELLOREPLY_HPP
