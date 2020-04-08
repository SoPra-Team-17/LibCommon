//
// Created by jonas on 07.04.20.
//

#include "ConfigDelivery.hpp"
#include "MessageContainer.hpp"

namespace spy::network::messages {

    const scenario::Scenario &ConfigDelivery::getLevel() const {
        return level;
    }

    const MatchConfig &ConfigDelivery::getSettings() const {
        return settings;
    }

    const std::vector<character::CharacterInformation> &
    ConfigDelivery::getCharacterSettings() const {
        return character_settings;
    }

    void to_json(nlohmann::json &j, const ConfigDelivery &c) {
        MessageContainer::common_to_json(j, c);
        j["level"] = c.level;
        j["settings"] = c.settings;
        j["character_settings"] = c.character_settings;
    }

    void from_json(const nlohmann::json &j, ConfigDelivery &c) {
        MessageContainer::common_from_json(j, c);
        j.at("level").get_to(c.level);
        j.at("settings").get_to(c.settings);
        j.at("character_settings").get_to(c.character_settings);
    }

    ConfigDelivery::ConfigDelivery() : MessageContainer{MessageTypeEnum::CONFIG_DELIVERY, {}} {}
}