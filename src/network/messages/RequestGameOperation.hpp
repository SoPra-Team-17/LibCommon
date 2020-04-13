//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_REQUESTGAMEOPERATION_HPP
#define LIBCOMMON_REQUESTGAMEOPERATION_HPP

#include <network/MessageContainer.hpp>

namespace spy::network::messages {

    class RequestGameOperation : public MessageContainer {
        public:
            RequestGameOperation();

            RequestGameOperation(const util::UUID &playerId, const util::UUID &characterId);

            [[nodiscard]] const util::UUID &getCharacterId() const;

            friend void to_json(nlohmann::json &j, const RequestGameOperation &r);

            friend void from_json(const nlohmann::json &j, RequestGameOperation &r);

            bool operator==(const RequestGameOperation &rhs) const;

        private:
            util::UUID characterId;

    };

}

#endif //LIBCOMMON_REQUESTGAMEOPERATION_HPP
