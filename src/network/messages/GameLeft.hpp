//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_GAMELEFT_HPP
#define LIBCOMMON_GAMELEFT_HPP

#include <network/MessageContainer.hpp>

namespace spy::network::messages {

    class GameLeft : public MessageContainer {
        public:
            GameLeft();

            explicit GameLeft(util::UUID playerId, util::UUID leftUserId);

            friend void to_json(nlohmann::json &j, const GameLeft &g);

            friend void from_json(const nlohmann::json &j, GameLeft &g);

        private:
            util::UUID leftUserId;
    };
}

#endif //LIBCOMMON_GAMELEFT_HPP
