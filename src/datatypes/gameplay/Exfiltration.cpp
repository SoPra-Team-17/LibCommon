//
// Created by jonas on 10.04.20.
//

#include "Exfiltration.hpp"

namespace spy::gameplay {

    Exfiltration::Exfiltration(bool successful, const util::Point &target,
                               const util::UUID &characterId, const util::Point &from) :
            CharacterOperation{OperationEnum::EXFILTRATION, successful, target, characterId},
            from{from} {}

    void to_json(nlohmann::json &j, const Exfiltration &e) {
        CharacterOperation::common_to_json(j, e);
        j["from"] = e.from;
    }

    void from_json(const nlohmann::json &j, Exfiltration &e) {
        CharacterOperation::common_from_json(j, e);
        j.at("from").get_to(e.from);
    }

    const util::Point &Exfiltration::getFrom() const {
        return from;
    }

    bool Exfiltration::isEqual(const BaseOperation &rhs_b) const {
        auto rhs = dynamic_cast<const Exfiltration &>(rhs_b);
        return isCharacterEqual(rhs) and from == rhs.from;
    }

    std::shared_ptr<BaseOperation> Exfiltration::clone() const {
        return std::make_shared<Exfiltration>(*this);
    }
}