/**
 * @file   Field.hpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Declaration of the field class.
 */

#ifndef LIBCOMMON_FIELD_HPP
#define LIBCOMMON_FIELD_HPP

#include <optional>
#include "gadgets/Gadget.hpp"
#include "FieldStateEnum.hpp"

namespace spy::scenario {
    /**
     * @brief Represents a field of the scenario.
     */
    class Field {
            using Gadget = spy::gadget::Gadget;

        public:
            Field() = default;

            void setFieldState(FieldStateEnum fieldState);
            void setDestroyed(bool isDestroyed);
            void setUpdated(bool isUpdated);
            void setInverted(bool isInverted);
            void setFoggy(bool isFoggy);
            void setGadget(std::optional<Gadget> g);
            void setChipAmount(std::optional<unsigned int> chipAmount);
            void setSafeIndex(std::optional<unsigned int> index);

            [[nodiscard]] FieldStateEnum getFieldState() const;
            [[nodiscard]] bool isDestroyed() const;
            [[nodiscard]] bool isUpdated() const;
            [[nodiscard]] bool isInverted() const;
            [[nodiscard]] bool isFoggy() const;
            [[nodiscard]] const std::optional<Gadget>& getGadget() const;
            [[nodiscard]] std::optional<unsigned int> getChipAmount() const;
            [[nodiscard]] std::optional<unsigned int> getSafeIndex() const;

        private:
            FieldStateEnum state = FieldStateEnum::FREE;
            std::optional<Gadget> gadget;
            bool destroyed = false;
            bool inverted = false;
            std::optional<unsigned int> chipAmount;
            std::optional<unsigned int> safeIndex;
            bool foggy = false;
            bool updated = false;
    };
}


#endif //LIBCOMMON_FIELD_HPP
