/**
 * @file   FieldMap.cpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Definition of the field map class.
 */

#include "FieldMap.hpp"

#include <iostream>

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
        FieldMap::setField(p.getX(), p.getY(), field);
    }

    const std::vector<std::vector<Field>> &FieldMap::getMap() const {
        return map;
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


    /**
     * @see playtechs.blogspot.com/2007/03/raytracing-on-grid.html for the original implementation
     */
    bool FieldMap::isLineOfSightFree(util::Point p1, util::Point p2) const {
        if (!isInside(p1) || !isInside(p2)) {
            throw std::invalid_argument("At least one point is outside the field map!");
        } else if (p1 == p2) {
            return true;
        }

        int dx = abs(p1.getX() - p2.getX());
        int dy = abs(p1.getY() - p2.getY());
        util::Point curPoint = p1;

        unsigned int fieldsToTraverse = dx + dy;
        int incX = (p2.getX() > p1.getX()) ? 1 : -1;
        int incY = (p2.getY() > p1.getY()) ? 1 : -1;
        int error = dx - dy;
        dx *= 2;                                            // scaling is needed to make sure the error term is integral
        dy *= 2;

        for (unsigned int fieldsVisited = 0; fieldsVisited < fieldsToTraverse; fieldsVisited++) {
            if (curPoint != p2 && curPoint != p1 && blocksSight(curPoint)) {
                return false;
            }

            if (error > 0) {
                curPoint.setX(curPoint.getX() + incX);
                error -= dy;
            } else if (error < 0) {
                curPoint.setY(curPoint.getY() + incY);
                error += dx;
            } else {
                error -= dy;
                error += dx;
                curPoint.setLocation(curPoint.getX() + incX, curPoint.getY() + incY);

                fieldsVisited++;
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