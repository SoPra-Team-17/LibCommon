//
// Created by jonas on 29.04.20.
//

#include "RetireAction.hpp"

namespace spy::gameplay {
    RetireAction::RetireAction() : BaseOperation(OperationEnum::RETIRE, false, {}) {}

    void to_json(nlohmann::json &j, const RetireAction &e) {
        BaseOperation::common_to_json(j, e);

    }

    void from_json(const nlohmann::json &j, RetireAction &e) {
        BaseOperation::common_from_json(j, e);
    }
}