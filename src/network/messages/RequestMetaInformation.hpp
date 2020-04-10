//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_REQUESTMETAINFORMATION_HPP
#define LIBCOMMON_REQUESTMETAINFORMATION_HPP

#include <string>
#include <network/MessageContainer.hpp>

namespace spy::network::messages {

    class RequestMetaInformation : public MessageContainer {
        public:
            RequestMetaInformation();

            RequestMetaInformation(const util::UUID &playerId, std::vector<std::string> keys);

            [[nodiscard]] const std::vector<std::string> &getKeys() const;

            friend void to_json(nlohmann::json &j, const RequestMetaInformation &r);

            friend void from_json(const nlohmann::json &j, RequestMetaInformation &r);

        private:
            std::vector<std::string> keys;
    };

}

#endif //LIBCOMMON_REQUESTMETAINFORMATION_HPP
