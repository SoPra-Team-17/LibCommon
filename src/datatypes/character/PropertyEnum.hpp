//
// Created by Carolin on 03.04.2020.
//

#ifndef LIBCOMMON_PROPERTYENUM_HPP
#define LIBCOMMON_PROPERTYENUM_HPP


namespace spy::character {
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


    //TODO: Wofuer ist das gut ? -> never used
    enum class NPCEnum {
        CAT,
        JANITOR
    };
}


#endif //LIBCOMMON_PROPERTYENUM_HPP
