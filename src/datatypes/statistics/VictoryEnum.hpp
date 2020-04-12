//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_VICTORYENUM_HPP
#define LIBCOMMON_VICTORYENUM_HPP

#include <nlohmann/json.hpp>

namespace spy::statistics {
    enum class VictoryEnum {
            INVALID,
            VICTORY_BY_IP,
            VICTORY_BY_COLLAR,
            VICTORY_BY_DRINKING,
            VICTORY_BY_SPILLING,
            VICTORY_BY_HP,
            VICTORY_BY_RANDOMNESS,
            VICTORY_BY_LEAVE,
            VICTORY_BY_KICK
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(VictoryEnum, {
        { VictoryEnum::INVALID, nullptr },
        { VictoryEnum::VICTORY_BY_IP, "VICTORY_BY_IP" },
        { VictoryEnum::VICTORY_BY_COLLAR, "VICTORY_BY_COLLAR" },
        { VictoryEnum::VICTORY_BY_DRINKING, "VICTORY_BY_DRINKING" },
        { VictoryEnum::VICTORY_BY_SPILLING, "VICTORY_BY_SPILLING" },
        { VictoryEnum::VICTORY_BY_HP, "VICTORY_BY_HP" },
        { VictoryEnum::VICTORY_BY_RANDOMNESS, "VICTORY_BY_RANDOMNESS" },
        { VictoryEnum::VICTORY_BY_LEAVE, "VICTORY_BY_LEAVE" },
        { VictoryEnum::VICTORY_BY_KICK, "VICTORY_BY_KICK" }
    })


}


#endif //LIBCOMMON_VICTORYENUM_HPP
