//
// Created by jonas on 09.04.20.
//

#ifndef LIBCOMMON_OPERATION_HPP
#define LIBCOMMON_OPERATION_HPP

#include <nlohmann/json.hpp>

namespace spy::gameplay {
    class Operation {
            friend void to_json(nlohmann::json &j, const Operation &o);

            friend void from_json(const nlohmann::json &j, Operation &o);
    };
}

#endif //LIBCOMMON_OPERATION_HPP
