//
// Created by jonas on 29.04.20.
//

#ifndef LIBCOMMON_RETIREACTION_HPP
#define LIBCOMMON_RETIREACTION_HPP

#include "CharacterOperation.hpp"

namespace spy::gameplay {
    class RetireAction : public CharacterOperation {
        public:
            RetireAction();

            friend void to_json(nlohmann::json &j, const RetireAction &e);

            friend void from_json(const nlohmann::json &j, RetireAction &e);

        private:
            bool isEqual(const BaseOperation &rhs) const override;
    };
}

#endif //LIBCOMMON_RETIREACTION_HPP
