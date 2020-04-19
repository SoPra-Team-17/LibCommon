/**
 * @file   Scenario.cpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Definition of the field map class.
 */

#include "Scenario.hpp"

namespace spy::scenario {

    void Scenario::setField(unsigned int x, unsigned int y, FieldStateEnum field) {
        scenario.at(y).at(x) = field;
    }

    void Scenario::setField(util::Point p, FieldStateEnum field) {
        setField(p.x, p.y, field);
    }

    FieldStateEnum Scenario::getField(unsigned int x, unsigned int y) const {
        return scenario.at(y).at(x);
    }

    FieldStateEnum Scenario::getField(util::Point p) const {
        return getField(p.x, p.y);
    }

    const std::vector<std::vector<FieldStateEnum>> &Scenario::getScenario() const {
        return scenario;
    }

    unsigned int Scenario::getNumberOfRows() const {
        return scenario.size();
    }

    unsigned int Scenario::getRowLength(unsigned int row) const {
        return scenario.at(row).size();
    }

    bool Scenario::operator==(const Scenario &rhs) const {
        return scenario == rhs.scenario;
    }

    bool Scenario::operator!=(const Scenario &rhs) const {
        return !(*this == rhs);
    }

    void to_json(nlohmann::json &j, const Scenario &s) {
        j["scenario"] = s.scenario;
    }

    void from_json(const nlohmann::json &j, Scenario &s) {
        j.at("scenario").get_to(s.scenario);
    }
}
