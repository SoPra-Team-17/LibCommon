//
// Created by jonas on 29.04.20.
//

#include "CatAction.hpp"

namespace spy::gameplay {
    CatAction::CatAction() : BaseOperation(OperationEnum::CAT_ACTION, false, {}) {}

    CatAction::CatAction(util::Point target) : BaseOperation(OperationEnum::CAT_ACTION, false, target) {}

    void to_json(nlohmann::json &j, const CatAction &e) {
        BaseOperation::common_to_json(j, e);
    }

    void from_json(const nlohmann::json &j, CatAction &e) {
        BaseOperation::common_from_json(j, e);
    }

    bool CatAction::isEqual(const BaseOperation &) const {
        // This class does not add members
        return true;
    }
}
