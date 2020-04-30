//
// Created by Carolin on 29.04.2020.
//

#include "BaseOperation.hpp"
#include <utility>

namespace spy::gameplay {

    BaseOperation::BaseOperation(OperationEnum type, bool successful, const util::Point &target) :
            type{type},
            successful{successful},
            target{target} {}

    OperationEnum BaseOperation::getType() const {
        return type;
    }

    bool BaseOperation::isSuccessful() const {
        return successful;
    }

    const util::Point &BaseOperation::getTarget() const {
        return target;
    }

    void BaseOperation::common_to_json(nlohmann::json &j, const BaseOperation &op) {
        j["type"] = op.type;
        j["successful"] = op.successful;
        j["target"] = op.target;
    }

    void BaseOperation::common_from_json(const nlohmann::json &j, BaseOperation &op) {
        j.at("type").get_to(op.type);
        j.at("successful").get_to(op.successful);
        j.at("target").get_to(op.target);
    }

    bool BaseOperation::operator==(const BaseOperation &rhs) const {
        std::cout << "Comparing BaseOperation" << std::endl;
        bool r = typeid(*this) == typeid(rhs) && isEqual(rhs);
        std::cout << "Comparing BaseOperation resulted in " << r << std::endl;
        return r;
    }

    bool BaseOperation::operator!=(const BaseOperation &rhs) const {
        return !(*this == rhs);
    }
}
