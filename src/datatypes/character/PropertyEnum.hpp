/**
 * @file   PropertyEnum.hpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Declaration of the character properties.
 */

#ifndef LIBCOMMON_PROPERTY_ENUM_HPP
#define LIBCOMMON_PROPERTY_ENUM_HPP

#include <nlohmann/json.hpp>

namespace spy::character {
    /**
     * Represents the different possible properties of characters.
     */
    enum class PropertyEnum {
        NIMBLENESS,
        SLUGGISHNESS,
        SPRYNESS,
        AGILITY,
        LUCKY_DEVIL,
        JINX,
        CLAMMY_CLOTHES,
        CONSTANT_CLAMMY_CLOTHES,
        ROBUST_STOMACH,
        TOUGHNESS,
        BABYSITTER,
        HONEY_TRAP,
        BANG_AND_BURN,
        FLAPS_AND_SEALS,
        TRADECRAFT,
        OBSERVATION
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(PropertyEnum , {
        { PropertyEnum::NIMBLENESS, "NIMBLENESS" },
        { PropertyEnum::SLUGGISHNESS, "SLUGGISHNESS" },
        { PropertyEnum::SPRYNESS, "SPRYNESS" },
        { PropertyEnum::AGILITY, "AGILITY" },
        { PropertyEnum::LUCKY_DEVIL, "LUCKY_DEVIL" },
        { PropertyEnum::JINX, "JINX" },
        { PropertyEnum::CLAMMY_CLOTHES, "CLAMMY_CLOTHES" },
        { PropertyEnum::CONSTANT_CLAMMY_CLOTHES, "CONSTANT_CLAMMY_CLOTHES" },
        { PropertyEnum::ROBUST_STOMACH, "ROBUST_STOMACH" },
        { PropertyEnum::TOUGHNESS, "TOUGHNESS" },
        { PropertyEnum::BABYSITTER, "BABYSITTER" },
        { PropertyEnum::HONEY_TRAP, "HONEY_TRAP" },
        { PropertyEnum::BANG_AND_BURN, "BANG_AND_BURN" },
        { PropertyEnum::FLAPS_AND_SEALS, "FLAPS_AND_SEALS" },
        { PropertyEnum::TRADECRAFT, "TRADECRAFT" },
        { PropertyEnum::OBSERVATION, "OBSERVATION" },
    })
}


#endif //LIBCOMMON_PROPERTY_ENUM_HPP
