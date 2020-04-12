/**
 * @file   FieldMap.cpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Definition of the field map class.
 */

#include "FieldMap.hpp"

namespace spy::scenario {

    FieldMap::FieldMap(const Scenario &scenario) {
        map.resize(scenario.getNumberOfRows());
        for (unsigned int y = 0; y < scenario.getNumberOfRows(); y++) {
            map.at(y).resize(scenario.getRowLength(y));
            for (unsigned int x = 0; x < scenario.getRowLength(y); x++) {
                setField(x, y, Field(scenario.getField(x, y)));
            }
        }
    }

    void FieldMap::setField(unsigned int x, unsigned int y, Field field) {
        map.at(y).at(x) = field;
    }

    void FieldMap::setField(spy::util::Point p, spy::scenario::Field field) {
        FieldMap::setField(p.getX(), p.getY(), field);
    }

    const Field &spy::scenario::FieldMap::getField(unsigned int x, unsigned int y) const {
        return map.at(y).at(x);
    }

    const Field &spy::scenario::FieldMap::getField(util::Point p) const {
        return getField(p.getX(), p.getY());
    }

    bool FieldMap::isInside(util::Point p) const {
        return !(p.getX() < 0 || p.getY() < 0
                 || map.size() <= static_cast<unsigned int>(p.getY())
                 || map.at(p.getY()).size() <= static_cast<unsigned int>(p.getX()));
    }

    void to_json(nlohmann::json &j, const FieldMap &m) {
        j["fieldMap"] = m.map;
    }

    void from_json(const nlohmann::json &j, FieldMap &m) {
        j.at("fieldMap").get_to(m.map);
    }
}