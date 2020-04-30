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

    bool Movement::operator==(const Movement &rhs) const {
        std::cout << "Comparing Movement" << std::endl;
        return std::tie(static_cast<const spy::gameplay::CharacterOperation &>(*this), from) ==
               std::tie(static_cast<const spy::gameplay::CharacterOperation &>(rhs), rhs.from);
    }

    bool Movement::operator!=(const Movement &rhs) const {
        return !(rhs == *this);
    }

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
}