//
// Created by jonas on 29.04.20.
//

#ifndef LIBCOMMON_SPYACTION_HPP
#define LIBCOMMON_SPYACTION_HPP

#include "CharacterOperation.hpp"

namespace spy::gameplay {
    class SpyAction : public CharacterOperation {
        public:
            SpyAction();

            SpyAction(util::UUID character, util::Point target);

            friend void to_json(nlohmann::json &j, const SpyAction &e);

            friend void from_json(const nlohmann::json &j, SpyAction &e);

            std::shared_ptr<BaseOperation> clone() const override;

        private:
            bool isEqual(const BaseOperation &rhs) const override;
    };
}

#endif //LIBCOMMON_SPYACTION_HPP
