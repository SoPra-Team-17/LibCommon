/**
* @file   Point.hpp
* @author Carolin
* @date   02.04.2020 (creation)
* @brief  Declaration of the point class.
*/

#ifndef LIBCOMMON_SRC_UTIL_POINT_HPP_
#define LIBCOMMON_SRC_UTIL_POINT_HPP_

namespace spy::util {
    /**
     * @brief Representation of coordinates.
     */
    class Point {
        public:
            Point() = default;

            Point(unsigned int x, unsigned int y);

            [[nodiscard]] unsigned int getX() const;

            void setX(unsigned int xCoord);

            [[nodiscard]] unsigned int getY() const;

            void setY(unsigned int yCoord);

            /**
             * Set x and y value of Point
             * @param xCoord new x value of Point
             * @param yCoord new y value of Point
             */
            void setLocation(unsigned int xCoord, unsigned int yCoord);

            /**
             * Translate x and y value of Point. New x and y values of Point are x+dx and y+dy
             * @param dx value to be added to x value of Point
             * @param dy value to be added to y value of Point
             * @return true if translation worked
             *         false if translation was not possible (x or y became negative)
             */
            bool translate(int dx, int dy);

            bool operator==(const Point &other) const;

            bool operator!=(const Point &other) const;

        private:
            unsigned int x;
            unsigned int y;

    };
}

#endif //LIBCOMMON_SRC_UTIL_POINT_HPP_
