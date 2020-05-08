//
// Created by jonas on 10.04.20.
//

#include "Movement.hpp"
#include <iostream>

namespace spy::gameplay {

    Movement::Movement(bool successful, const util::Point &target, const util::UUID &characterId,
                       const util::Point &from) :
            CharacterOperation(OperationEnum::MOVEMENT, successful, target, characterId),
            from(from) {}

    const util::Point &Movement::getFrom() const {
        return from;
    }


    unsigned int Movement::getMoveDistance(const util::Point &p1, const util::Point &p2) {
        return std::max(std::abs(p1.x - p2.x), std::abs(p1.y - p2.y));
    }

    void to_json(nlohmann::json &j, const Movement &m) {
        CharacterOperation::common_to_json(j, m);
        j["from"] = m.from;
    }

    void from_json(const nlohmann::json &j, Movement &m) {
        CharacterOperation::common_from_json(j, m);
        j.at("from").get_to(m.from);
    }

    bool Movement::isEqual(const BaseOperation &rhs_b) const {
        auto rhs = dynamic_cast<const Movement &>(rhs_b);
        return isCharacterEqual(rhs) && from == rhs.from;
    }

    std::shared_ptr<BaseOperation> Movement::clone() const {
        return std::make_shared<Movement>(*this);
    }
}