/**
 * @file   GameOperation.cpp
 * @author Jonas
 * @date   07.04.2020 (creation)
 * @brief  Definition of a game operation message.
 */

#ifndef LIBCOMMON_GAMEOPERATION_HPP
#define LIBCOMMON_GAMEOPERATION_HPP

#include "network/MessageContainer.hpp"
#include "network/RoleEnum.hpp"
#include "datatypes/gameplay/State.hpp"
#include "datatypes/gameplay/CharacterOperation.hpp"
#include "datatypes/matchconfig/MatchConfig.hpp"

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
             * Validate message according role and operation type and if operation is allowed in current state.
             * @param playerRole        Role of the player who sent the message.
             * @param state             Current state of the game.
             * @param activeCharacter   Character that move was requested from.
             * @param config            Configuration of the current match.
             * @return true if message is valid
             *         false if message is not valid
             */
            [[nodiscard]] bool validate(RoleEnum playerRole, const gameplay::State &state, util::UUID activeCharacter,
                                        const MatchConfig &config) const;

            friend std::ostream &operator<<(std::ostream &os, const GameOperation &metaInformation);


        private:
            std::shared_ptr<gameplay::BaseOperation> operation;
    };
}


#endif //LIBCOMMON_GAMEOPERATION_HPP
