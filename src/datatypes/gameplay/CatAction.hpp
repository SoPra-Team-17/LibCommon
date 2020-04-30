//
// Created by jonas on 29.04.20.
//

#ifndef LIBCOMMON_CATACTION_HPP
#define LIBCOMMON_CATACTION_HPP

#include "BaseOperation.hpp"

namespace spy::gameplay {
    class CatAction : public BaseOperation {
        public:
            CatAction();

            friend void to_json(nlohmann::json &j, const CatAction &e);

            friend void from_json(const nlohmann::json &j, CatAction &e);

        private:
            bool isEqual(const BaseOperation &rhs) const override;
    };
}

#endif //LIBCOMMON_CATACTION_HPP
