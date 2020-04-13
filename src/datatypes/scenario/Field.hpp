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
#include "util/OptionalSerialization.hpp"

namespace spy::scenario {
    /**
     * @brief Represents a field of the scenario.
     */
    class Field {
            using Gadget = spy::gadget::Gadget;

        public:
            Field() = default;
            explicit Field(FieldStateEnum fieldState);

            void setFieldState(FieldStateEnum fieldState);
            void setDestroyed(std::optional<bool> isDestroyed);
            void setUpdated(std::optional<bool> isUpdated);
            void setInverted(std::optional<bool> isInverted);
            void setFoggy(bool isFoggy);
            void setGadget(std::optional<Gadget> g);
            void setChipAmount(std::optional<unsigned int> chipAmount);
            void setSafeIndex(std::optional<unsigned int> index);

            [[nodiscard]] FieldStateEnum getFieldState() const;
            [[nodiscard]] std::optional<bool> isDestroyed() const;
            [[nodiscard]] std::optional<bool> isUpdated() const;

            [[nodiscard]] std::optional<bool> isInverted() const;

            [[nodiscard]] bool isFoggy() const;

            [[nodiscard]] const std::optional<Gadget> &getGadget() const;

            [[nodiscard]] std::optional<unsigned int> getChipAmount() const;

            [[nodiscard]] std::optional<unsigned int> getSafeIndex() const;

            friend void to_json(nlohmann::json &j, const Field &f);

            friend void from_json(const nlohmann::json &j, Field &f);

            bool operator==(const Field &rhs) const;

        private:
            FieldStateEnum state = FieldStateEnum::FREE;
            std::optional<Gadget> gadget;
            std::optional<bool> destroyed;
            std::optional<bool> inverted;
            std::optional<unsigned int> chipAmount;
            std::optional<unsigned int> safeIndex;
            bool foggy = false;
            std::optional<bool> updated;
    };
}


#endif //LIBCOMMON_FIELD_HPP
