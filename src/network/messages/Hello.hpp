//
// Created by marco on 09.04.20.
//

#ifndef LIBCOMMON_HELLO_HPP
#define LIBCOMMON_HELLO_HPP

#include <string>
#include "network/MessageContainer.hpp"
#include <network/RoleEnum.hpp>

namespace spy::network::messages {
    class Hello : public MessageContainer {
        public:
            Hello();

            Hello(util::UUID playerId, std::string &name, RoleEnum &role);

            [[nodiscard]] const std::string &getName() const;

            [[nodiscard]] const RoleEnum &getRole() const;

            friend void to_json(nlohmann::json &j, const Hello &h);

            friend void from_json(const nlohmann::json &j, Hello &h);

        private:
            std::string name;
            RoleEnum role = RoleEnum::INVALID;
    };
}

#endif //LIBCOMMON_HELLO_HPP
