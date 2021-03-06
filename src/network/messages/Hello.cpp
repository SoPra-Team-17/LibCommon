//
// Created by marco on 09.04.20.
//

#include "Hello.hpp"
#include <utility>

namespace spy::network::messages {

    Hello::Hello() : MessageContainer(MessageTypeEnum::HELLO, {}) {}

    Hello::Hello(util::UUID clientId, std::string name, RoleEnum role) : MessageContainer(
            MessageTypeEnum::HELLO, clientId), name(std::move(name)), role(role) {}

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

    bool Hello::operator==(const Hello &rhs) const {
        return isEqual(rhs) &&
               name == rhs.name &&
               role == rhs.role;
    }

    bool Hello::validate() const {
        return this->role != spy::network::RoleEnum::INVALID;
    }
}