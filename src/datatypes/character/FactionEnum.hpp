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
     * Represents the different possible factions. (internal representation, not sent over network)
     */
    enum class FactionEnum {
            INVALID,
            PLAYER1,
            PLAYER2,
            NEUTRAL //!< NPC
    };
}

#endif //LIBCOMMON_FACTIONENUM_HPP
