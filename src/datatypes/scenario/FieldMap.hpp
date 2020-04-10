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
#include "Field.hpp"

namespace spy::scenario {
    class FieldMap {
        public:
            FieldMap() = default;

        private:
            std::vector<std::vector<Field>> map;
    };
}

#endif //LIBCOMMON_FIELD_MAP_HPP
