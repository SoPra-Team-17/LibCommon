/**
 * @file   Character.cpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Definition of the point class.
 */

#include "Point.hpp"

namespace spy::util {
    Point::Point(unsigned int x, unsigned int y) : x(x), y(y) {}

    unsigned int Point::getX() const {
        return x;
    }

    void Point::setX(unsigned int xCord) {
        Point::x = xCord;
    }

    unsigned int Point::getY() const {
        return y;
    }

    void Point::setY(unsigned int yCord) {
        Point::y = yCord;
    }

    void Point::setLocation(unsigned int xCoord, unsigned int yCoord) {
        Point::x = xCoord;
        Point::y = yCoord;
    }

    bool Point::translate(int dx, int dy) {
        if ((int)Point::x + dx < 0 || (int)Point::y + dy < 0) {
            return false;
        }
        setLocation(Point::x + dx, Point::y + dy);
        return true;
    }

    bool Point::operator==(const Point &other) const {
        return this->x == other.x && this->y == other.y;
    }

    bool Point::operator!=(const Point &other) const {
        return !(other == *this);
    }
}  // namespace spy::util
