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

namespace spy::scenario {
    class FieldMap {
        public:
            FieldMap() = default;

            void setField(unsigned int x, unsigned int y, Field field);

            void setField(util::Point p, Field field);

            [[nodiscard]] const Field &getField(unsigned int x, unsigned int y) const;

            [[nodiscard]] const Field &getField(util::Point p) const;

            [[nodiscard]] bool isInside(util::Point p) const;

        private:
            std::vector<std::vector<Field>> map;
    };
}

#endif //LIBCOMMON_FIELD_MAP_HPP
