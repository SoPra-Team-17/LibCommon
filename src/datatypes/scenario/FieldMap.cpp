/**
 * @file   FieldMap.cpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Definition of the field map class.
 */

#include "FieldMap.hpp"

namespace spy::scenario {

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
                 || map.size() < static_cast<unsigned int>(p.getY())
                 || map.at(p.getY()).size() < static_cast<unsigned int>(p.getX()));
    }
}