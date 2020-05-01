/**
 * @file   FieldMap.hpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Declaration of the field map class.
 */

#ifndef LIBCOMMON_FIELD_MAP_HPP
#define LIBCOMMON_FIELD_MAP_HPP

#include <vector>
#include <nlohmann/json.hpp>
#include "util/Point.hpp"
#include "Field.hpp"
#include "Scenario.hpp"

namespace spy::scenario {
    /**
     * @brief Represents the field during the game.
     */
    class FieldMap {
        public:
            FieldMap() = default;

            explicit FieldMap(const Scenario &scenario);

            void setMap(std::vector<std::vector<Field>> fieldMap);

            void setField(unsigned int x, unsigned int y, Field field);

            void setField(util::Point p, Field field);

            [[nodiscard]] const std::vector<std::vector<Field>> &getMap() const;

            [[nodiscard]] const Field &getField(unsigned int x, unsigned int y) const;

            [[nodiscard]] Field &getField(unsigned int x, unsigned int y);

            [[nodiscard]] const Field &getField(util::Point p) const;

            [[nodiscard]] Field &getField(util::Point p);

            [[nodiscard]] bool isInside(util::Point p) const;

            /**
             * Checks if a given field blocks the line of sight (thus is a wall or a fireplace).
             * @param p Coordinate of the field to check.
             * @return True if it blocks the line of sight, else false.
             */
            [[nodiscard]] bool blocksSight(util::Point p) const;

            /**
             * Checks if a given field is accessible by a character.
             * @param p Coordinate of the field to check.
             * @return True if the field is free or a bar seat, otherwise false.
             */
            [[nodiscard]] bool isAccessible(util::Point p) const;

            /**
             * Checks whether the line of sight between to fields is blocked.
             * @param p1 First field.
             * @param p2 Second field.
             * @return False if the line of sight is blocked (by a fireplace or wall field), otherwise true.
             */
            [[nodiscard]] bool isLineOfSightFree(util::Point p1, util::Point p2) const;

            /**
             * Checks whether the line of sight between to fields is blocked.
             * @param p1 First field.
             * @param p2 Second field.
             * @param blocksLine function returning true for points blocking the sight line
             * @return False if the line of sight is blocked, otherwise true.
             * @see playtechs.blogspot.com/2007/03/raytracing-on-grid.html for the original implementation
             */
            template<typename T>
            [[nodiscard]] bool isLineOfSightFree(util::Point p1, util::Point p2, T blocksLine) const {
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
                    if (currentPoint != p1 && blocksLine(currentPoint)) {
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

            friend void to_json(nlohmann::json &j, const FieldMap &m);

            friend void from_json(const nlohmann::json &j, FieldMap &m);

            bool operator==(const FieldMap &rhs) const;

        private:

            std::vector<std::vector<Field>> map;
    };
}

#endif //LIBCOMMON_FIELD_MAP_HPP
