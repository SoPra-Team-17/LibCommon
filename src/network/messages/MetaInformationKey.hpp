//
// Created by Carolin on 26.04.2020.
//

#ifndef LIBCOMMON_METAINFORMATIONKEY_HPP
#define LIBCOMMON_METAINFORMATIONKEY_HPP

#include <nlohmann/json.hpp>

namespace spy::network::messages {
    enum class MetaInformationKey {
            INVALID,
            SPECTATOR_COUNT,
            SPECTATOR_MEMBERS,
            CONFIGURATION_SCENARIO,
            CONFIGURATION_MATCH_CONFIG,
            CONFIGURATION_CHARACTER_INFORMATION,
            GAME_REMAINING_PAUSE_TIME,
            FACTION_PLAYER1,
            FACTION_PLAYER2,
            FACTION_NEUTRAL,
            GADGETS_PLAYER1,
            GADGETS_PLAYER2
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(MetaInformationKey, {
        { MetaInformationKey::INVALID, nullptr },
        { MetaInformationKey::SPECTATOR_COUNT, "Spectator.Count" },
        { MetaInformationKey::SPECTATOR_MEMBERS, "Spectator.Members" },
        { MetaInformationKey::CONFIGURATION_SCENARIO, "Configuration.Scenario" },
        { MetaInformationKey::CONFIGURATION_MATCH_CONFIG, "Configuration.MatchConfig" },
        { MetaInformationKey::CONFIGURATION_CHARACTER_INFORMATION, "Configuration.CharacterInformation" },
        { MetaInformationKey::GAME_REMAINING_PAUSE_TIME, "Game.RemainingPauseTime" },
        { MetaInformationKey::FACTION_PLAYER1, "Faction.Player1" },
        { MetaInformationKey::FACTION_PLAYER2, "Faction.Player2" },
        { MetaInformationKey::FACTION_NEUTRAL, "Faction.Neutral" },
        { MetaInformationKey::GADGETS_PLAYER1, "Gadgets.Player1" },
        { MetaInformationKey::GADGETS_PLAYER2, "Gadgets.Player2" }
    })
}

#endif //LIBCOMMON_METAINFORMATIONKEY_HPP
