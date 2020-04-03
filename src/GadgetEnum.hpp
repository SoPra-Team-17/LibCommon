//
// Created by jonas on 03.04.20.
//

#ifndef LIBCOMMON_GADGETENUM_HPP
#define LIBCOMMON_GADGETENUM_HPP

#include <nlohmann/json.hpp>

namespace spy::gadget {
    enum class GadgetEnum {
        INVALID,
        HAIRDRYER,
        MOLEDIE,
        TECHNICOLOUR_PRISM,
        BOWLER_BLADE,
        MAGNETIC_WATCH,
        POISON_PILLS,
        LASER_COMPACT,
        ROCKET_PEN,
        GAS_GLOSS,
        MOTHBALL_POUCH,
        FOG_TIN,
        GRAPPLE,
        WIRETAP_WITH_EARPLUGS,
        DIAMOND_COLLAR,
        JETPACK,
        CHICKEN_FEED,
        NUGGET,
        MIRROR_OF_WILDERNESS,
        POCKET_LITTER,
        COCKTAIL
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(GadgetEnum, {
        { GadgetEnum::INVALID, nullptr },
        { GadgetEnum::ROCKET_PEN, "ROCKET_PEN" },
    })

}

#endif //LIBCOMMON_GADGETENUM_HPP
