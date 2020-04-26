//
// Created by marco on 10.04.20.
//

#include "RequestMetaInformation.hpp"

#include <utility>

namespace spy::network::messages {

    RequestMetaInformation::RequestMetaInformation() : MessageContainer{MessageTypeEnum::REQUEST_META_INFORMATION,
                                                                        {}} {}

    RequestMetaInformation::RequestMetaInformation(const util::UUID &playerId, std::vector<MetaInformationKey> keys)
            : MessageContainer{MessageTypeEnum::REQUEST_META_INFORMATION, playerId}, keys(std::move(keys)) {}


    void to_json(nlohmann::json &j, const RequestMetaInformation &r) {
        MessageContainer::common_to_json(j, r);
        j["keys"] = r.keys;
    }

    void from_json(const nlohmann::json &j, RequestMetaInformation &r) {
        MessageContainer::common_from_json(j, r);
        j.at("keys").get_to(r.keys);
    }

    const std::vector<MetaInformationKey> &RequestMetaInformation::getKeys() const {
        return keys;
    }

    bool RequestMetaInformation::operator==(const RequestMetaInformation &rhs) const {
        return isEqual(rhs) &&
               keys == rhs.keys;
    }

    bool RequestMetaInformation::validate(RoleEnum playerRole) const {
        return playerRole != RoleEnum::INVALID &&
               std::find(keys.begin(), keys.end(), MetaInformationKey::INVALID) == keys.end();
    }
}