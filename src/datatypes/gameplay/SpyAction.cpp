//
// Created by jonas on 29.04.20.
//

#include "SpyAction.hpp"

namespace spy::gameplay {
    SpyAction::SpyAction() : BaseOperation(OperationEnum::SPY_ACTION, false, {}) {}

    void to_json(nlohmann::json &j, const SpyAction &e) {
        BaseOperation::common_to_json(j, e);
    }

    void from_json(const nlohmann::json &j, SpyAction &e) {
        BaseOperation::common_from_json(j, e);
    }
}