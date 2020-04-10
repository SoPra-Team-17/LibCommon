/**
 * @file   FieldMap.hpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Declaration of the field map class.
 */

#ifndef LIBCOMMON_SCENARIO_HPP
#define LIBCOMMON_SCENARIO_HPP

#include <vector>
#include <nlohmann/json.hpp>
#include "FieldStateEnum.hpp"
#include "Field.hpp"

namespace spy::scenario {
    class Scenario {
        public:
            Scenario() = default;

            [[nodiscard]] FieldStateEnum getField(unsigned int x, unsigned int y) const;

            friend void from_json(const nlohmann::json &j, Scenario &s);
        private:
            std::vector<std::vector<FieldStateEnum>> scenario;
    };
}


#endif //LIBCOMMON_SCENARIO_HPP
