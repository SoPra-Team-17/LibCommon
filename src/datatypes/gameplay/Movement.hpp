/**
 * @file   Movement.hpp
 * @author Jonas
 * @brief  Movement operation
 */

#ifndef LIBCOMMON_MOVEMENT_HPP
#define LIBCOMMON_MOVEMENT_HPP

#include "Operation.hpp"
#include <util/Point.hpp>

namespace spy::gameplay {
    class Movement : public Operation {
        public:
            Movement() = default;

            Movement(bool successful, const util::Point &target, const util::UUID &characterId,
                     const util::Point &from);

            [[nodiscard]] const util::Point &getFrom() const;

            /**
             * Calculates the distance between two points.
             * @param p1 First point.
             * @param p2 Second point.
             * @return Distance between the points.
             * @note The distance is measured using a "king's move metric".
             */
            static unsigned int getMoveDistance(const util::Point &p1, const util::Point &p2);

            friend void to_json(nlohmann::json &j, const Movement &m);

            friend void from_json(const nlohmann::json &j, Movement &m);

            bool operator==(const Movement &rhs) const;

            bool operator!=(const Movement &rhs) const;
        private:
            util::Point from{};
    };

}

#endif //LIBCOMMON_MOVEMENT_HPP
