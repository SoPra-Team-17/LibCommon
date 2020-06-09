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
            void operator+=(const Point &rhs);

            void operator-=(const Point &rhs);

            Point operator+(const Point &rhs) const;

            Point operator-(const Point &rhs) const;

            bool operator==(const Point &other) const;

            bool operator!=(const Point &other) const;

            bool operator<(const Point &other) const;

            friend std::ostream &operator<<(std::ostream &os, const Point &p);

            friend void to_json(nlohmann::json &j, const Point &p);

            friend void from_json(const nlohmann::json &j, Point &p);

            int x = 0;
            int y = 0;
    };
}

#endif //LIBCOMMON_SRC_UTIL_POINT_HPP_
