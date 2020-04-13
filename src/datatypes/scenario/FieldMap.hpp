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

            [[nodiscard]] const Field &getField(util::Point p) const;

            [[nodiscard]] bool isInside(util::Point p) const;

            friend void to_json(nlohmann::json &j, const FieldMap &m);

            friend void from_json(const nlohmann::json &j, FieldMap &m);

            bool operator==(const FieldMap &rhs) const;

        private:
            std::vector<std::vector<Field>> map;
    };
}

#endif //LIBCOMMON_FIELD_MAP_HPP
