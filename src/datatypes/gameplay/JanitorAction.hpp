//
// Created by jonas on 29.04.20.
//

#ifndef LIBCOMMON_JANITORACTION_HPP
#define LIBCOMMON_JANITORACTION_HPP

#include "CopyableOperation.hpp"

namespace spy::gameplay {
    class JanitorAction : public CopyableOperation<JanitorAction> {
        public:
            JanitorAction();

            explicit JanitorAction(util::Point target);

            friend void to_json(nlohmann::json &j, const JanitorAction &e);

            friend void from_json(const nlohmann::json &j, JanitorAction &e);

        private:
            [[nodiscard]] bool isEqual(const BaseOperation &rhs) const override;
    };
}

#endif //LIBCOMMON_JANITORACTION_HPP
