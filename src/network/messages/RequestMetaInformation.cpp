//
// Created by marco on 10.04.20.
//

#include "RequestMetaInformation.hpp"

#include <utility>

namespace spy::network::messages {

    RequestMetaInformation::RequestMetaInformation() : MessageContainer{MessageTypeEnum::REQUEST_META_INFORMATION,
                                                                        {}} {}

    RequestMetaInformation::RequestMetaInformation(const util::UUID &playerId, std::vector<std::string> keys)
            : MessageContainer{MessageTypeEnum::REQUEST_META_INFORMATION, playerId}, keys(std::move(keys)) {}


    void to_json(nlohmann::json &j, const RequestMetaInformation &r) {
        MessageContainer::common_to_json(j, r);
        j["keys"] = r.keys;
    }

    void from_json(const nlohmann::json &j, RequestMetaInformation &r) {
        MessageContainer::common_from_json(j, r);
        j.at("keys").get_to(r.keys);
    }

    const std::vector<std::string> &RequestMetaInformation::getKeys() const {
        return keys;
    }

    bool RequestMetaInformation::operator==(const RequestMetaInformation &rhs) const {
        return isEqual(rhs) &&
               keys == rhs.keys;
    }

    bool RequestMetaInformation::validate(RoleEnum playerRole) const {
        if (playerRole == RoleEnum::INVALID) {
            return false;
        }

        std::vector<std::string> allowedKeys{"Spectator.Count", "Spectator.Members", "Configuration.Scenario",
                                             "Configuration.MatchConfig", "Configuration.CharacterInformation",
                                             "Game.RemainingPauseTime", "Fraction.Player1", "Fraction.Player2",
                                             "Fraction.Neutral", "Gadgets.Player1", "Gadgets.Player2"};
        for (auto s: keys) {
            if (std::find(allowedKeys.begin(), allowedKeys.end(), s) == allowedKeys.end()) {
                return false;
            }
        }

        return true;
    }
}