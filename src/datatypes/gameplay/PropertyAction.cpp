//
// Created by jonas on 10.04.20.
//

#include "PropertyAction.hpp"

namespace spy::gameplay {
    PropertyAction::PropertyAction(bool successful, const util::Point &target, const util::UUID &characterId,
                                   character::PropertyEnum usedProperty) :
            CharacterOperation(OperationEnum::PROPERTY_ACTION, successful, target, characterId),
            usedProperty(usedProperty) {}

    character::PropertyEnum PropertyAction::getUsedProperty() const {
        return usedProperty;
    }

    void to_json(nlohmann::json &j, const PropertyAction &p) {
        CharacterOperation::common_to_json(j, p);
        j["usedProperty"] = p.usedProperty;
    }

    void from_json(const nlohmann::json &j, PropertyAction &p) {
        CharacterOperation::common_from_json(j, p);
        j.at("usedProperty").get_to(p.usedProperty);
    }

    bool PropertyAction::operator==(const PropertyAction &rhs) const {
        return std::tie(static_cast<const spy::gameplay::CharacterOperation &>(*this), usedProperty) ==
               std::tie(static_cast<const spy::gameplay::CharacterOperation &>(rhs), rhs.usedProperty);
    }

    bool PropertyAction::operator!=(const PropertyAction &rhs) const {
        return !(rhs == *this);
    }
}