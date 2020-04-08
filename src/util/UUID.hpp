//
// Created by jonas on 02.04.20.
//

#ifndef LIBCOMMON_UUID_HPP
#define LIBCOMMON_UUID_HPP

#include <nlohmann/json.hpp>

namespace spy::util {
    class UUID {
        public:
            UUID() = default;;

            // TODO implement UUID class
            friend void to_json(nlohmann::json &j, const UUID &c);

            friend void from_json(const nlohmann::json &j, UUID &c);
    };
}

#endif //LIBCOMMON_UUID_HPP
