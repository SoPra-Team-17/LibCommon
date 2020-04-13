//
// Created by jonas on 07.04.20.
//

#include "Scenario.hpp"

namespace spy::scenario {
    void to_json(nlohmann::json &/*j*/, const spy::scenario::Scenario &/*s*/) {

    }

    void from_json(const nlohmann::json &/*j*/, spy::scenario::Scenario &/*s*/) {

    }

    bool Scenario::operator==(const Scenario &/*rhs*/) const {
        return true;
    }
}