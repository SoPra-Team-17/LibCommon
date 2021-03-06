//
// Created by jonas on 29.04.20.
//

#include "JanitorAction.hpp"

namespace spy::gameplay {
    JanitorAction::JanitorAction() : BaseOperation(OperationEnum::JANITOR_ACTION, false, {}) {}

    JanitorAction::JanitorAction(util::Point target) : BaseOperation(OperationEnum::JANITOR_ACTION, false, target) {}

    void to_json(nlohmann::json &j, const JanitorAction &e) {
        BaseOperation::common_to_json(j, e);
    }

    void from_json(const nlohmann::json &j, JanitorAction &e) {
        BaseOperation::common_from_json(j, e);
    }

    bool JanitorAction::isEqual(const BaseOperation &) const {
        return true;
    }

    std::shared_ptr<BaseOperation> JanitorAction::clone() const {
        return std::make_shared<JanitorAction>(*this);
    }
}