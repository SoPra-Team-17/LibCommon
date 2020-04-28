//
// Created by jonas on 28.04.20.
//

#ifndef LIBCOMMON_GADGETVALIDATOR_HPP
#define LIBCOMMON_GADGETVALIDATOR_HPP

#include <datatypes/gameplay/GadgetAction.hpp>

namespace spy::gameplay {
    class GadgetValidator {
        public:
            // Static class
            GadgetValidator() = delete;

            // TODO add gadgets
            static bool validateRocketPen(GadgetAction a);
    };
}

#endif //LIBCOMMON_GADGETVALIDATOR_HPP
