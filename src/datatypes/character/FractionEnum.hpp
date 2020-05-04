/**
 * @file   FractionEnum.hpp
 * @author Marco Deuscher
 * @date   04.05.2020 (creation)
 * @brief  Declaration of Fraction enum
 */

#ifndef LIBCOMMON_FRACTIONENUM_HPP
#define LIBCOMMON_FRACTIONENUM_HPP

namespace spy::character {
    /**
     * Represents the different possible fractions.
     */
    enum class FractionEnum {
            INVALID,
            PLAYER1,
            PLAYER2
    };
}

#endif //LIBCOMMON_FRACTIONENUM_HPP
