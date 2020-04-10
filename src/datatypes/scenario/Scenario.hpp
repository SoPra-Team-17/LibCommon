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
#include "util/Point.hpp"

namespace spy::scenario {
    /**
     * @brief Represents the scenario encoded in the scenario configuration.
     */
    class Scenario {
        public:
            Scenario() = default;

            [[nodiscard]] FieldStateEnum getField(unsigned int x, unsigned int y) const;

            [[nodiscard]] FieldStateEnum getField(util::Point p) const;

            [[nodiscard]] unsigned int getNumberOfRows() const;

            [[nodiscard]] unsigned int getRowLength(unsigned int row) const;

            friend void to_json(nlohmann::json &j, const Scenario &s);

            friend void from_json(const nlohmann::json &j, Scenario &s);
        private:
            std::vector<std::vector<FieldStateEnum>> scenario;
    };
}


#endif //LIBCOMMON_SCENARIO_HPP
