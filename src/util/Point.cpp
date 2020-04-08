/**
 * @file   Character.cpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Definition of the point class.
 */

#include "Point.hpp"

namespace spy::util {
    Point::Point(int x, int y) : x(x), y(y) {}

    int Point::getX() const {
        return x;
    }

    void Point::setX(int xCord) {
        Point::x = xCord;
    }

    int Point::getY() const {
        return y;
    }

    void Point::setY(int yCord) {
        Point::y = yCord;
    }

    void Point::setLocation(int xCoord, int yCoord) {
        Point::x = xCoord;
        Point::y = yCoord;
    }

    void Point::operator+=(const Point &rhs) {
        setLocation(Point::x + rhs.x, Point::y + rhs.y);
    }

    void Point::operator-=(const Point &rhs) {
        setLocation(Point::x - rhs.x, Point::y - rhs.y);
    }

    bool Point::operator==(const Point &other) const {
        return Point::x == other.x && Point::y == other.y;
    }

    bool Point::operator!=(const Point &other) const {
        return !(other == *this);
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
