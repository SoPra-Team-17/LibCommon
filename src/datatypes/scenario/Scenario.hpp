//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_SCENARIO_HPP
#define LIBCOMMON_SCENARIO_HPP

#include <nlohmann/json.hpp>

namespace spy::scenario {
    class Scenario {
            friend void to_json(nlohmann::json &j, const Scenario &s);

            friend void from_json(const nlohmann::json &j, Scenario &s);

        public:
            bool operator==(const Scenario &rhs) const;

    };
}


#endif //LIBCOMMON_SCENARIO_HPP
