/**
 * @file   PropertyAction.hpp
 * @author Jonas
 * @date   10.04.2020 (creation)
 * @brief  PropertyAction operation
 */

#ifndef LIBCOMMON_PROPERTYACTION_HPP
#define LIBCOMMON_PROPERTYACTION_HPP

#include "CharacterOperation.hpp"
#include "datatypes/character/PropertyEnum.hpp"
#include "util/OptionalSerialization.hpp"

namespace spy::gameplay {
    class PropertyAction : public CharacterOperation {
        public:
            PropertyAction() = default;

            PropertyAction(bool successful, const util::Point &target, const util::UUID &characterId,
                           character::PropertyEnum usedProperty, std::optional<bool> isEnemy = std::nullopt);

            [[nodiscard]] character::PropertyEnum getUsedProperty() const;

            [[nodiscard]] std::optional<bool> getIsEnemy() const;

            friend void to_json(nlohmann::json &j, const PropertyAction &p);

            friend void from_json(const nlohmann::json &j, PropertyAction &p);

            [[nodiscard]] std::shared_ptr<BaseOperation> clone() const override;

        private:
            character::PropertyEnum usedProperty;

            std::optional<bool> isEnemy;

            [[nodiscard]] bool isEqual(const BaseOperation &rhs) const override;
    };
}
#endif //LIBCOMMON_PROPERTYACTION_HPP
