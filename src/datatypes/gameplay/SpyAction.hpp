//
// Created by jonas on 29.04.20.
//

#ifndef LIBCOMMON_SPYACTION_HPP
#define LIBCOMMON_SPYACTION_HPP

#include "BaseOperation.hpp"

namespace spy::gameplay {
    class SpyAction : public BaseOperation {
        public:
            SpyAction();

            friend void to_json(nlohmann::json &j, const SpyAction &e);

            friend void from_json(const nlohmann::json &j, SpyAction &e);

        private:
            bool isEqual(const BaseOperation &rhs) const override;
    };
}

#endif //LIBCOMMON_SPYACTION_HPP
