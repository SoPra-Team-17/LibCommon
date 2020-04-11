//
// Created by jonas on 10.04.20.
//

#include "Operation.hpp"
#include <utility>

namespace spy::gameplay {

    Operation::Operation(OperationEnum type, bool successful, const util::Point &target) :
            type{type},
            successful{successful},
            target{target} {}

    Operation::Operation(OperationEnum type, bool successful, const util::Point &target, util::UUID characterId) :
            type{type},
            successful{successful},
            target{target},
            characterId{characterId} {}

    void Operation::common_to_json(nlohmann::json &j, const Operation &op) {
        j["type"] = op.type;
        j["successful"] = op.successful;
        j["target"] = op.target;
        j["characterId"] = op.characterId;
    }

    void Operation::common_from_json(const nlohmann::json &j, Operation &op) {
        j.at("type").get_to(op.type);
        j.at("successful").get_to(op.successful);
        j.at("target").get_to(op.target);
        if (j.find("characterId") != j.end()) {
            j.at("characterId").get_to(op.characterId);
        } else {
            op.characterId->clear();
        }
    }

    void to_json(nlohmann::json &j, const Operation &o) {
        Operation::common_to_json(j, o);
    }

    void from_json(const nlohmann::json &j, Operation &o) {
        Operation::common_from_json(j, o);
    }

    OperationEnum Operation::getType() const {
        return type;
    }

    bool Operation::isSuccessful() const {
        return successful;
    }

    const util::Point &Operation::getTarget() const {
        return target;
    }

    const std::optional<util::UUID> &Operation::getCharacterId() const {
        return characterId;
    }

    bool Operation::operator==(const Operation &rhs) const {
        return std::tie(type, successful, target, characterId) ==
               std::tie(rhs.type, rhs.successful, rhs.target, rhs.characterId);
    }

    bool Operation::operator!=(const Operation &rhs) const {
        return !(rhs == *this);
    }

}