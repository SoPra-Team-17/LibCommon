/**
 * @file   FactionEnum.hpp
 * @author Marco Deuscher
 * @date   04.05.2020 (creation)
 * @brief  Declaration of Fraction enum
 */

#ifndef LIBCOMMON_FACTIONENUM_HPP
#define LIBCOMMON_FACTIONENUM_HPP

namespace spy::character {
    /**
     * Represents the different possible fractions.
     */
    enum class FactionEnum {
            INVALID,
            PLAYER1,
            PLAYER2
    };
}

#endif //LIBCOMMON_FACTIONENUM_HPP
