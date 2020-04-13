//
// Created by marco on 10.04.20.
//

#include "State.hpp"

namespace spy::gameplay {
    void to_json(nlohmann::json &/*j*/, const State &/*s*/) {

    }

    void from_json(const nlohmann::json &/*j*/, State &/*s*/) {

    }

    bool State::operator==(const State &/*rhs*/) const {
        return true;
    }
}