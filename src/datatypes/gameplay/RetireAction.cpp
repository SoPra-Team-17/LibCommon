//
// Created by jonas on 29.04.20.
//

#include "RetireAction.hpp"

namespace spy::gameplay {
    RetireAction::RetireAction() : CharacterOperation(OperationEnum::RETIRE, false, {}) {}

    void to_json(nlohmann::json &j, const RetireAction &e) {
        CharacterOperation::common_to_json(j, e);
    }

    void from_json(const nlohmann::json &j, RetireAction &e) {
        CharacterOperation::common_from_json(j, e);
    }

    bool RetireAction::isEqual(const BaseOperation &rhs) const {
        return isCharacterEqual(dynamic_cast<const CharacterOperation &>(rhs));
    }
}