//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_STATE_HPP
#define LIBCOMMON_STATE_HPP

#include <nlohmann/json.hpp>

namespace spy::gameplay {
    class State {
            friend void to_json(nlohmann::json &j, const State &s);

            friend void from_json(const nlohmann::json &j, State &s);
    };
}


#endif //LIBCOMMON_STATE_HPP
