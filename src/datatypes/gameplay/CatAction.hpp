//
// Created by jonas on 29.04.20.
//

#ifndef LIBCOMMON_CATACTION_HPP
#define LIBCOMMON_CATACTION_HPP

#include "CopyableOperation.hpp"

namespace spy::gameplay {
    class CatAction : public CopyableOperation<CatAction> {
        public:
            CatAction();

            explicit CatAction(util::Point target);

            friend void to_json(nlohmann::json &j, const CatAction &e);

            friend void from_json(const nlohmann::json &j, CatAction &e);

        private:
            [[nodiscard]] bool isEqual(const BaseOperation &rhs) const override;
    };
}

#endif //LIBCOMMON_CATACTION_HPP
