/**
 * @file   FieldStateEnum.hpp
 * @author Dominik Authaler
 * @date   07.04.2020 (creation)
 * @brief  Declaration of the enum for the filed states.
 */


#ifndef LIBCOMMON_FIELD_STATE_ENUM_HPP
#define LIBCOMMON_FIELD_STATE_ENUM_HPP

namespace spy::scenario {
    enum class FieldStateEnum {
        BAR_TABLE,
        ROULETTE_TABLE,
        WALL,
        FREE,
        BAR_SEAT,
        SAFE,
        FIREPLACE
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(FieldStateEnum, {
        { FieldStateEnum::WALL, "WALL" },
        { FieldStateEnum::BAR_TABLE, "BAR_TABLE" },
        { FieldStateEnum::FREE, "FREE" },
        { FieldStateEnum::ROULETTE_TABLE, "ROULETTE_TABLE" },
        { FieldStateEnum::BAR_SEAT, "BAR_SEAT" },
        { FieldStateEnum::SAFE, "SAFE" },
        { FieldStateEnum::FIREPLACE, "FIREPLACE" }
    })
}

#endif //LIBCOMMON_FIELD_STATE_ENUM_HPP
