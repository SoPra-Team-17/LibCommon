//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_CONFIGDELIVERY_HPP
#define LIBCOMMON_CONFIGDELIVERY_HPP

#include <datatypes/scenario/Scenario.hpp>
#include <datatypes/matchconfig/MatchConfig.hpp>
#include <vector>
#include <datatypes/character/CharacterInformation.hpp>
#include "MessageContainer.hpp"

namespace spy::network::messages {
    class ConfigDelivery : public MessageContainer {
        public:

            ConfigDelivery();

            [[nodiscard]] const scenario::Scenario &getLevel() const;

            [[nodiscard]] const MatchConfig &getSettings() const;

            [[nodiscard]] const std::vector<character::CharacterInformation> &getCharacterSettings() const;

            friend void to_json(nlohmann::json &j, const ConfigDelivery &c);

            friend void from_json(const nlohmann::json &j, ConfigDelivery &c);

        private:
            scenario::Scenario level;
            MatchConfig settings;
            std::vector<character::CharacterInformation> character_settings;
    };
}

#endif //LIBCOMMON_CONFIGDELIVERY_HPP
