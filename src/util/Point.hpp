/**
* @file   Point.hpp
* @author Carolin
* @date   02.04.2020 (creation)
* @brief  Declaration of the point class.
*/

#ifndef LIBCOMMON_SRC_UTIL_POINT_HPP_
#define LIBCOMMON_SRC_UTIL_POINT_HPP_

#include <nlohmann/json.hpp>

namespace spy::util {
    /**
     * @brief Representation of coordinates.
     */
    class Point {
        public:
            Point() = default;

            Point(int x, int y);

            [[nodiscard]] int getX() const;

            void setX(int xCoord);

            [[nodiscard]] int getY() const;

            void setY(int yCoord);

            /**
             * Set x and y value of Point
             * @param xCoord new x value of Point
             * @param yCoord new y value of Point
             */
            void setLocation(int xCoord, int yCoord);

            void operator+=(const Point &rhs);

            void operator-=(const Point &rhs);

            Point operator+(const Point &rhs) const;

            Point operator-(const Point &rhs) const;

            bool operator==(const Point &other) const;

            bool operator!=(const Point &other) const;

            friend void to_json(nlohmann::json &j, const Point &p);

            friend void from_json(const nlohmann::json &j, Point &p);

        private:
            int x;
            int y;

    };
}

#endif //LIBCOMMON_SRC_UTIL_POINT_HPP_
