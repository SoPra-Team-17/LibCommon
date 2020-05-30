/**
 * @file   PropertyAction.hpp
 * @author Jonas
 * @date   10.04.2020 (creation)
 * @brief  PropertyAction operation
 */

#include "PropertyAction.hpp"

namespace spy::gameplay {
    PropertyAction::PropertyAction(bool successful, const util::Point &target, const util::UUID &characterId,
                                   character::PropertyEnum usedProperty, std::optional<bool> isEnemy) :
            CharacterOperation(OperationEnum::PROPERTY_ACTION, successful, target, characterId),
            usedProperty(usedProperty), isEnemy(isEnemy) {}

    character::PropertyEnum PropertyAction::getUsedProperty() const {
        return usedProperty;
    }

    std::optional<bool> PropertyAction::getIsEnemy() const {
        return isEnemy;
    }

    void PropertyAction::setIsEnemy(std::optional<bool> enemy) {
        this->isEnemy = enemy;
    }

    void to_json(nlohmann::json &j, const PropertyAction &p) {
        CharacterOperation::common_to_json(j, p);
        j["usedProperty"] = p.usedProperty;
        j["isEnemy"] = p.isEnemy;
    }

    void from_json(const nlohmann::json &j, PropertyAction &p) {
        CharacterOperation::common_from_json(j, p);
        j.at("usedProperty").get_to(p.usedProperty);
        j.at("isEnemy").get_to(p.isEnemy);
    }

    bool PropertyAction::isEqual(const BaseOperation &rhs_b) const {
        auto rhs = dynamic_cast<const PropertyAction &>(rhs_b);
        return isCharacterEqual(rhs) && usedProperty == rhs.usedProperty && isEnemy == rhs.isEnemy;
    }

    std::shared_ptr<BaseOperation> PropertyAction::clone() const {
        return std::make_shared<PropertyAction>(*this);
    }
}