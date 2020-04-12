//
// Created by marco on 10.04.20.
//

#include "RequestReplay.hpp"

namespace spy::network::messages {
    RequestReplay::RequestReplay() : MessageContainer{MessageTypeEnum::REQUEST_REPLAY, {}} {}

    RequestReplay::RequestReplay(const util::UUID &playerId) : MessageContainer{MessageTypeEnum::REQUEST_REPLAY,
                                                                                playerId} {}


    void to_json(nlohmann::json &j, const RequestReplay &r) {
        MessageContainer::common_to_json(j, r);
    }

    void from_json(const nlohmann::json &j, RequestReplay &r) {
        MessageContainer::common_from_json(j, r);
    }
}
