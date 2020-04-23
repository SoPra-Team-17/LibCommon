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

    bool FieldMap::isInside(util::Point p) const {
        return !(p.x < 0 || p.y < 0
                 || map.size() <= static_cast<unsigned int>(p.y)
                 || map.at(p.y).size() <= static_cast<unsigned int>(p.x));
    }


    /**
     * @see playtechs.blogspot.com/2007/03/raytracing-on-grid.html for the original implementation
     */
    bool FieldMap::isLineOfSightFree(util::Point p1, util::Point p2) const {
        if (!isInside(p1) || !isInside(p2)) {
            throw std::invalid_argument("At least one point is outside the field map!");
        } else if (p1 == p2) {
            return true;
        }

        int dx = abs(p1.x - p2.x);
        int dy = abs(p1.y - p2.y);

        int incX = (p2.x > p1.x) ? 1 : -1;
        int incY = (p2.y > p1.y) ? 1 : -1;
        int error = dx - dy;
        // scaling is needed to make sure the error term is integral
        dx *= 2;
        dy *= 2;
        auto currentPoint = p1;
        while (currentPoint != p2) {
            if (currentPoint != p1 && blocksSight(currentPoint)) {
                return false;
            }

            if (error > 0) {
                currentPoint.x += incX;
                error -= dy;
            } else if (error < 0) {
                currentPoint.y += incY;
                error += dx;
            } else {
                error -= dy;
                error += dx;
                currentPoint += {incX, incY};
            }
        }

        return true;
    }

    bool FieldMap::blocksSight(util::Point p) const {
        return (getField(p).getFieldState() == FieldStateEnum::WALL
                || getField(p).getFieldState() == FieldStateEnum::FIREPLACE);
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