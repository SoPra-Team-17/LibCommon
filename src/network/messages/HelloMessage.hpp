//
// Created by marco on 09.04.20.
//

#ifndef LIBCOMMON_HELLOMESSAGE_HPP
#define LIBCOMMON_HELLOMESSAGE_HPP

#include <string>
#include "network/MessageContainer.hpp"
#include <network/RoleEnum.hpp>

namespace spy::network::messages {
    class HelloMessage : public MessageContainer {
        public:
            HelloMessage();

            HelloMessage(util::UUID playerId, std::string &name, RoleEnum &role);

            [[nodiscard]] const std::string &getName() const;

            [[nodiscard]] const RoleEnum &getRole() const;

            friend void to_json(nlohmann::json &j, const HelloMessage &h);

            friend void from_json(const nlohmann::json &j, HelloMessage &h);

        private:
            std::string name;
            RoleEnum role = RoleEnum::INVALID;
    };
}

#endif //LIBCOMMON_HELLOMESSAGE_HPP
