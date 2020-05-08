//
// Created by jonas on 29.04.20.
//

#include "SpyAction.hpp"

namespace spy::gameplay {
    SpyAction::SpyAction() : CharacterOperation(OperationEnum::SPY_ACTION, false, {}) {}

    SpyAction::SpyAction(util::UUID character, util::Point target) :
            CharacterOperation(OperationEnum::SPY_ACTION, false, target, character) {}

    void to_json(nlohmann::json &j, const SpyAction &e) {
        CharacterOperation::common_to_json(j, e);
    }

    void from_json(const nlohmann::json &j, SpyAction &e) {
        CharacterOperation::common_from_json(j, e);
    }

    bool SpyAction::isEqual(const BaseOperation &rhs) const {
        return isCharacterEqual(dynamic_cast<const SpyAction &>(rhs));
    }

    std::shared_ptr<BaseOperation> SpyAction::clone() const {
        return std::make_shared<SpyAction>(*this);
    }
}