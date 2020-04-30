//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_GAMEOPERATION_HPP
#define LIBCOMMON_GAMEOPERATION_HPP

#include <network/MessageContainer.hpp>
#include <datatypes/gameplay/CharacterOperation.hpp>
#include <network/RoleEnum.hpp>
#include <datatypes/gameplay/State.hpp>

namespace spy::network::messages {
    class GameOperation : public MessageContainer {
        public:
            GameOperation();

            GameOperation(util::UUID playerId, std::shared_ptr<gameplay::BaseOperation> operation);

            [[nodiscard]] const std::shared_ptr<gameplay::BaseOperation> &getOperation() const;

            friend void to_json(nlohmann::json &j, const GameOperation &g);

            friend void from_json(const nlohmann::json &j, GameOperation &g);

            bool operator==(const GameOperation &rhs) const;

            /**
             * validate message according role and operation type and if operation is allowed in current state
             * @param playerRole role of the player who sent the message
             * @param state current state of the game
             * @return true if message is valid
             *         false if message is not valid
             */
            [[nodiscard]] bool validate(RoleEnum playerRole, spy::gameplay::State &state) const;

            friend std::ostream &operator<<(std::ostream &os, const GameOperation &metaInformation);


        private:
            std::shared_ptr<gameplay::BaseOperation> operation;
    };
}


#endif //LIBCOMMON_GAMEOPERATION_HPP
