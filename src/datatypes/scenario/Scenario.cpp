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
        setField(p.getX(), p.getY(), field);
    }

    FieldStateEnum Scenario::getField(unsigned int x, unsigned int y) const {
        return scenario.at(y).at(x);
    }

    FieldStateEnum Scenario::getField(util::Point p) const {
        return getField(p.getX(), p.getY());
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
        if (scenario.size() != rhs.scenario.size()) {
            return false;
        } else {
            for (unsigned int row = 0; row < scenario.size(); row++) {
                if (scenario.at(row).size() != rhs.scenario.at(row).size()) {
                    return false;
                }

                for (unsigned int col = 0; col < scenario.at(row).size(); col++) {
                    if (scenario.at(row).at(col) != rhs.scenario.at(row).at(col)) {
                        return false;
                    }
                }
            }

            return true;
        }
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