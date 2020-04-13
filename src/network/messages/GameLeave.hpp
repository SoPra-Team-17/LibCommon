//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_GAMELEAVE_HPP
#define LIBCOMMON_GAMELEAVE_HPP

#include <network/MessageContainer.hpp>

namespace spy::network::messages {
    class GameLeave : public MessageContainer {
        public:
            GameLeave();

            explicit GameLeave(util::UUID playerId);

            friend void to_json(nlohmann::json &j, const GameLeave &g);

            friend void from_json(const nlohmann::json &j, GameLeave &g);

            bool operator==(const GameLeave &rhs) const;
    };
}

#endif //LIBCOMMON_GAMELEAVE_HPP
