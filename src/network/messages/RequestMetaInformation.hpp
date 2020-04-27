//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_REQUESTMETAINFORMATION_HPP
#define LIBCOMMON_REQUESTMETAINFORMATION_HPP

#include <string>
#include <network/MessageContainer.hpp>
#include <network/RoleEnum.hpp>
#include "MetaInformationKey.hpp"

namespace spy::network::messages {

    class RequestMetaInformation : public MessageContainer {
        public:
            RequestMetaInformation();

            RequestMetaInformation(const util::UUID &playerId, std::vector<MetaInformationKey> keys);

            [[nodiscard]] const std::vector<MetaInformationKey> &getKeys() const;

            friend void to_json(nlohmann::json &j, const RequestMetaInformation &r);

            friend void from_json(const nlohmann::json &j, RequestMetaInformation &r);

            bool operator==(const RequestMetaInformation &rhs) const;

            /**
             * validate message according role and keys
             * @param playerRole role of the player who sent the message
             * @return true if message is valid
             *         false if message is not valid
             */
            [[nodiscard]] bool validate(RoleEnum playerRole) const;

        private:
            std::vector<MetaInformationKey> keys;
    };

}

#endif //LIBCOMMON_REQUESTMETAINFORMATION_HPP
