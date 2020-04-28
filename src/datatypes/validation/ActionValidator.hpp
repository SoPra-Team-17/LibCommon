/**
 * @brief validate() functions for all possible Operations
 */

#ifndef LIBCOMMON_ACTIONVALIDATOR_HPP
#define LIBCOMMON_ACTIONVALIDATOR_HPP


#include <datatypes/gameplay/State.hpp>
#include <datatypes/gameplay/Movement.hpp>

namespace spy::gameplay {
    class ActionValidator {
        public:
            // Static class
            ActionValidator() = delete;

            static bool validate(const State &s, Movement m);
    };
}

#endif //LIBCOMMON_ACTIONVALIDATOR_HPP
