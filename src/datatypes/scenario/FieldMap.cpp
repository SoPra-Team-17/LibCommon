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

    void FieldMap::setMap(std::vector<std::vector<Field>> fieldMap) {
        FieldMap::map = std::move(fieldMap);
    }

    void FieldMap::setField(unsigned int x, unsigned int y, Field field) {
        map.at(y).at(x) = field;
    }

    void FieldMap::setField(spy::util::Point p, spy::scenario::Field field) {
        FieldMap::setField(p.x, p.y, field);
    }

    const std::vector<std::vector<Field>> &FieldMap::getMap() const {
        return map;
    }

    const Field &spy::scenario::FieldMap::getField(unsigned int x, unsigned int y) const {
        return map.at(y).at(x);
    }

    const Field &spy::scenario::FieldMap::getField(util::Point p) const {
        return getField(p.x, p.y);
    }

    Field &spy::scenario::FieldMap::getField(unsigned int x, unsigned int y) {
        return map.at(y).at(x);
    }

    Field &spy::scenario::FieldMap::getField(util::Point p) {
        return getField(p.x, p.y);
    }

    bool FieldMap::isInside(util::Point p) const {
        return !(p.x < 0 || p.y < 0
                 || map.size() <= static_cast<unsigned int>(p.y)
                 || map.at(p.y).size() <= static_cast<unsigned int>(p.x));
    }

    bool FieldMap::blocksSight(util::Point p) const {
        return (getField(p).getFieldState() == FieldStateEnum::WALL
                || getField(p).getFieldState() == FieldStateEnum::FIREPLACE);
    }

    bool FieldMap::isAccessible(util::Point p) const {
        return (getField(p).getFieldState() == FieldStateEnum::FREE
                || getField(p).getFieldState() == FieldStateEnum::BAR_SEAT);
    }

    bool FieldMap::isLineOfSightFree(util::Point p1, util::Point p2) const {
        return isLineOfSightFree(p1, p2, [this](util::Point currentPoint) { return blocksSight(currentPoint); });
    }

    void to_json(nlohmann::json &j, const FieldMap &m) {
        j["fieldMap"] = m.map;
    }

    void from_json(const nlohmann::json &j, FieldMap &m) {
        j.at("fieldMap").get_to(m.map);
    }

    bool FieldMap::operator==(const FieldMap &rhs) const {
        return map == rhs.map;
    }
}