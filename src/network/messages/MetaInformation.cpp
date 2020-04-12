//
// Created by jonas on 12.04.20.
//

#include "MetaInformation.hpp"

#include <utility>
#include <iostream>

namespace spy::network::messages {

    MetaInformation::MetaInformation() : MessageContainer{MessageTypeEnum::META_INFORMATION, {}} {}

    const std::map<std::string, MetaInformation::Info> &MetaInformation::getInformation() const {
        return information;
    }

    MetaInformation::MetaInformation(const util::UUID &playerId,
                                     std::map<std::string, Info> information) :
            MessageContainer(MessageTypeEnum::META_INFORMATION, playerId),
            information(std::move(information)) {}

    void to_json(nlohmann::json &j, const MetaInformation &m) {
        MessageContainer::common_to_json(j, m);
        j["information"] = m.information;
    }

    void from_json(const nlohmann::json &j, MetaInformation &m) {
        MessageContainer::common_from_json(j, m);

        for (const auto &item : j.at("information").items()) {
            if (item.key() == "Spectator.Count") {
                m.information.insert({"Spectator.Count", item.value().get<int>()});
            } else if (item.key() == "Spectator.Members") {
                m.information.insert({"Spectator.Members", item.value().get<std::vector<std::string>>()});
            } else if (item.key() == "Configuration.Scenario") {
                m.information.insert({"Configuration.Scenario", item.value().get<scenario::Scenario>()});
            } else if (item.key() == "Configuration.Matchconfig") {
                m.information.insert({"Configuration.Matchconfig", item.value().get<MatchConfig>()});
            } else if (item.key() == "Configuration.CharacterInformation") {
                m.information.insert({"Configuration.CharacterInformation",
                                      item.value().get<std::vector<character::CharacterInformation>>()});
            } else if (item.key() == "Game.RemainingPauseTime") {
                m.information.insert({"Game.RemainingPauseTime", item.value().get<int>()});
            } else if (item.key() == "Faction.Player1") {
                m.information.insert({"Faction.Player1", item.value().get<std::vector<util::UUID>>()});
            } else if (item.key() == "Faction.Player2") {
                m.information.insert({"Faction.Player2", item.value().get<std::vector<util::UUID>>()});
            } else if (item.key() == "Faction.Neutral") {
                m.information.insert({"Faction.Neutral", item.value().get<std::vector<util::UUID>>()});
            } else if (item.key() == "Gadgets.Player1") {
                m.information.insert({"Gadgets.Player1", item.value().get<std::vector<gadget::GadgetEnum>>()});
            } else if (item.key() == "Gadgets.Player2") {
                m.information.insert({"Gadgets.Player2", item.value().get<std::vector<gadget::GadgetEnum>>()});
            }
        }
    }
}