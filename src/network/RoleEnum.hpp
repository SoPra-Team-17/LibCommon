//
// Created by marco on 09.04.20.
//

#ifndef LIBCOMMON_ROLEENUM_HPP
#define LIBCOMMON_ROLEENUM_HPP
#include <nlohmann/json.hpp>

namespace spy::network {
    enum class RoleEnum {
            SPECTATOR,
            PLAYER,
            AI
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(RoleEnum, {
        { RoleEnum::SPECTATOR, "SPECTATOR" },
        { RoleEnum::PLAYER, "PLAYER" },
        { RoleEnum::AI, "AI" },
    })
}

#endif //LIBCOMMON_ROLEENUM_HPP
