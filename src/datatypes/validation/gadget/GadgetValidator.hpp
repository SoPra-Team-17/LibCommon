//
// Created by jonas on 28.04.20.
//

#ifndef LIBCOMMON_GADGETVALIDATOR_HPP
#define LIBCOMMON_GADGETVALIDATOR_HPP

#include <datatypes/gameplay/GadgetAction.hpp>
#include <datatypes/gameplay/State.hpp>

namespace spy::gameplay {
    class GadgetValidator {
        public:
            // Static class
            GadgetValidator() = delete;

            // TODO add gadgets
            static bool validateRocketPen(const State &s, GadgetAction a);
    };
}

#endif //LIBCOMMON_GADGETVALIDATOR_HPP
