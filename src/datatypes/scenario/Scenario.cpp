/**
 * @file   Scenario.cpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Definition of the field map class.
 */

#include "Scenario.hpp"

namespace spy::scenario {

    FieldStateEnum Scenario::getField(unsigned int x, unsigned int y) const {
        return scenario.at(y).at(x);
    }

    void from_json(const nlohmann::json &j, Scenario &s) {
        j.at("scenario").get_to(s.scenario);
    }
}