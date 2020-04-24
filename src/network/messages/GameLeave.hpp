//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_GAMELEAVE_HPP
#define LIBCOMMON_GAMELEAVE_HPP

#include <network/MessageContainer.hpp>
#include <network/RoleEnum.hpp>

namespace spy::network::messages {
    class GameLeave : public MessageContainer {
        public:
            GameLeave();

            explicit GameLeave(util::UUID playerId);

            friend void to_json(nlohmann::json &j, const GameLeave &g);

            friend void from_json(const nlohmann::json &j, GameLeave &g);

            bool operator==(const GameLeave &rhs) const;

            /**
             * validate message according role
             * @param playerRole role of the player who sent the message
             * @return true if message is valid
             *         false if message is not valid
             */
            [[nodiscard]] bool validate(RoleEnum playerRole) const;
    };
}

#endif //LIBCOMMON_GAMELEAVE_HPP
