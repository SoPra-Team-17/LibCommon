//
// Created by jonas on 29.04.20.
//

#ifndef LIBCOMMON_RETIREACTION_HPP
#define LIBCOMMON_RETIREACTION_HPP

#include "BaseOperation.hpp"

namespace spy::gameplay {
    class RetireAction : public BaseOperation {
        public:
            RetireAction();

            friend void to_json(nlohmann::json &j, const RetireAction &e);

            friend void from_json(const nlohmann::json &j, RetireAction &e);
    };
}

#endif //LIBCOMMON_RETIREACTION_HPP
