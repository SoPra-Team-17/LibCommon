/**
 * @file   Character.cpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Definition of the point class.
 */

#include "Point.hpp"

namespace spy::util {

    void Point::operator+=(const Point &rhs) {
        x += rhs.x;
        y += rhs.y;
    }

    void Point::operator-=(const Point &rhs) {
        x -= rhs.x;
        y -= rhs.y;
    }

    Point Point::operator+(const Point &rhs) const {
        return {this->x + rhs.x, this->y + rhs.y};
    }

    Point Point::operator-(const Point &rhs) const {
        return {this->x - rhs.x, this->y - rhs.y};
    }

    bool Point::operator==(const Point &other) const {
        return Point::x == other.x && Point::y == other.y;
    }

    bool Point::operator!=(const Point &other) const {
        return !(other == *this);
    }

    std::ostream &operator<<(std::ostream &os, const Point &p) {
        os << "[" << p.x << "|" << p.y << "]";
        return os;
    }

    void to_json(nlohmann::json &j, const spy::util::Point &p) {
        j["x"] = p.x;
        j["y"] = p.y;
    }

    void from_json(const nlohmann::json &j, spy::util::Point &p) {
        j.at("x").get_to(p.x);
        j.at("y").get_to(p.y);
    }

}  // namespace spy::util
