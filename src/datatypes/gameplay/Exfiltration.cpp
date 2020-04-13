//
// Created by jonas on 10.04.20.
//

#include "Exfiltration.hpp"

namespace spy::gameplay {

    Exfiltration::Exfiltration(bool successful, const util::Point &target,
                               const util::UUID &characterId, const util::Point &from) :
            Operation{OperationEnum::EXFILTRATION, successful, target, characterId},
            from{from} {}

    void to_json(nlohmann::json &j, const Exfiltration &e) {
        Operation::common_to_json(j, e);
        j["from"] = e.from;
    }

    void from_json(const nlohmann::json &j, Exfiltration &e) {
        Operation::common_from_json(j, e);
        j.at("from").get_to(e.from);
    }

    const util::Point &Exfiltration::getFrom() const {
        return from;
    }

    bool Exfiltration::operator==(const Exfiltration &rhs) const {
        return std::tie(static_cast<const spy::gameplay::Operation &>(*this), from) ==
               std::tie(static_cast<const spy::gameplay::Operation &>(rhs), rhs.from);
    }

    bool Exfiltration::operator!=(const Exfiltration &rhs) const {
        return !(rhs == *this);
    }
}