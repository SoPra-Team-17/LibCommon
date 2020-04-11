//
// Created by jonas on 10.04.20.
//

#include "Movement.hpp"

namespace spy::gameplay {

    Movement::Movement(bool successful, const util::Point &target, const util::UUID &characterId,
                       const util::Point &from) :
            Operation(OperationEnum::MOVEMENT, successful, target, characterId),
            from(from) {}

    bool Movement::operator==(const Movement &rhs) const {
        return std::tie(static_cast<const spy::gameplay::Operation &>(*this), from) ==
               std::tie(static_cast<const spy::gameplay::Operation &>(rhs), rhs.from);
    }

    bool Movement::operator!=(const Movement &rhs) const {
        return !(rhs == *this);
    }

    const util::Point &Movement::getFrom() const {
        return from;
    }

    void to_json(nlohmann::json &j, const Movement &m) {
        Operation::common_to_json(j, m);
        j["from"] = m.from;
    }

    void from_json(const nlohmann::json &j, Movement &m) {
        Operation::common_from_json(j, m);
        j.at("from").get_to(m.from);
    }
}