/**
 * @file   PropertyAction.hpp
 * @author Jonas
 * @brief  PropertyAction operation
 */

#ifndef LIBCOMMON_PROPERTYACTION_HPP
#define LIBCOMMON_PROPERTYACTION_HPP

#include "Operation.hpp"
#include <datatypes/character/PropertyEnum.hpp>

namespace spy::gameplay {
    class PropertyAction : public Operation {
        public:
            PropertyAction() = default;

            PropertyAction(bool successful, const util::Point &target, const util::UUID &characterId,
                           character::PropertyEnum usedProperty);

            [[nodiscard]] character::PropertyEnum getUsedProperty() const;

            bool operator==(const PropertyAction &rhs) const;

            bool operator!=(const PropertyAction &rhs) const;

            friend void to_json(nlohmann::json &j, const PropertyAction &p);

            friend void from_json(const nlohmann::json &j, PropertyAction &p);

        private:
            character::PropertyEnum usedProperty;
    };
}
#endif //LIBCOMMON_PROPERTYACTION_HPP