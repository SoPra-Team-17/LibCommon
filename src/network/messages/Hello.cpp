//
// Created by marco on 09.04.20.
//

#include "Hello.hpp"

namespace spy::network::messages {

    Hello::Hello() : MessageContainer(MessageTypeEnum::HELLO, {}) {}

    Hello::Hello(util::UUID playerId, std::string &name, RoleEnum &role) : MessageContainer(
            MessageTypeEnum::HELLO, playerId), name(name), role(role) {}

    const std::string &Hello::getName() const {
        return name;
    }

    const RoleEnum &Hello::getRole() const {
        return role;
    }

    void to_json(nlohmann::json &j, const spy::network::messages::Hello &h) {
        MessageContainer::common_to_json(j, h);
        j["role"] = h.role;
        j["name"] = h.name;
    }

    void from_json(const nlohmann::json &j, spy::network::messages::Hello &h) {
        MessageContainer::common_from_json(j, h);
        j.at("role").get_to(h.role);
        j.at("name").get_to(h.name);
    }
}