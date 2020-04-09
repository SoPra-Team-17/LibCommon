//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_GAMEOPERATION_HPP
#define LIBCOMMON_GAMEOPERATION_HPP

#include <network/messages/MessageContainer.hpp>
#include <datatypes/gameplay/Operation.hpp>

namespace spy::network::messages {
    class GameOperation : public MessageContainer {
        public:
            GameOperation();

            GameOperation(util::UUID playerId, gameplay::Operation operation);

            friend void to_json(nlohmann::json &j, const GameOperation &g);

            friend void from_json(const nlohmann::json &j, GameOperation &g);

        private:
            gameplay::Operation operation;
    };
}


#endif //LIBCOMMON_GAMEOPERATION_HPP
