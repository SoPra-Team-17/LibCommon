/**
* @file   PropertyExecutor.hpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
*/

#ifndef LIBCOMMON_PROPERTYEXECUTOR_HPP
#define LIBCOMMON_PROPERTYEXECUTOR_HPP

#include "datatypes/gameplay/PropertyAction.hpp"
#include "datatypes/gameplay/State.hpp"
#include "datatypes/matchconfig/MatchConfig.hpp"

namespace spy::gameplay {

    /**
     * @brief methods to apply properties
     */
    class PropertyExecutor {
        public:
            PropertyExecutor() = delete;

            static bool execute(State &s, const PropertyAction &a, const MatchConfig &config);

        private:
            static bool executeObservation(State &s, const PropertyAction &a, const MatchConfig &config);

            static bool executeBangAndBurn(State &s, const PropertyAction &a);
    };

}
#endif //LIBCOMMON_PROPERTYEXECUTOR_HPP
