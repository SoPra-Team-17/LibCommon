/**
 * @file   Field.hpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Declaration of the field class.
 */

#ifndef LIBCOMMON_FIELD_HPP
#define LIBCOMMON_FIELD_HPP

#include <optional>
#include "datatypes/gadgets/Gadget.hpp"
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

            /**
             * Setter for the state of the roulette table on this field.
             * @param isDestroyed State of the roulette table.
             * @note  This param can only be set if the field state is ROULETTE_TABLE.
             */
            void setDestroyed(std::optional<bool> isDestroyed);
            void setUpdated(std::optional<bool> isUpdated);

            /**
             * Setter for the inversion of the roulette table on this field.
             * @param isInverted Inversion state of the roulette table.
             * @note  This param can only be set if the field state is ROULETTE_TABLE.
             */
            void setInverted(std::optional<bool> isInverted);
            void setFoggy(bool isFoggy);
            void incrementFogCounter();
            void resetFogCounter();
            void setGadget(std::optional<Gadget> g);
            void removeGadget();

            /**
             * Setter for the chip amount of the roulette table on this field.
             * @param chips Chip amount.
             * @note  This param can only be set if the field state is ROULETTE_TABLE.
             */
            void setChipAmount(std::optional<unsigned int> chipAmount);

            /**
             * Setter for the index of the safe on this field.
             * @param index Safe index.
             * @note  This param can only be set if the field state is SAFE.
             */
            void setSafeIndex(std::optional<unsigned int> index);

            [[nodiscard]] FieldStateEnum getFieldState() const;

            /**
             * Getter for the state of the roulette table.
             * @return True if the roulette table is destroyed, else false.
             * @note   The return value only contains a value if the field's state is ROULETTE_TABLE.
             */
            [[nodiscard]] std::optional<bool> isDestroyed() const;
            [[nodiscard]] std::optional<bool> isUpdated() const;

            /**
             * Getter for the inversion of the roulette table probabilities.
             * @return True if the roulette table is inverted, else false.
             * @note   The return value only contains a value if the field's state is ROULETTE_TABLE.
             */
            [[nodiscard]] std::optional<bool> isInverted() const;

            [[nodiscard]] bool isFoggy() const;

            [[nodiscard]] unsigned int getFogCounter() const;

            [[nodiscard]] const std::optional<Gadget> &getGadget() const;

            /**
             * Getter for the amount of chips of the roulette table.
             * @return Chip amount.
             * @note   The return value only contains a value if the field's state is ROULETTE_TABLE.
             */
            [[nodiscard]] std::optional<unsigned int> getChipAmount() const;

            /**
             * Getter for the index of the safe.
             * @return Safe index.
             * @note   The return value only contains a value if the field's state is SAFE.
             */
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
            unsigned int fogCounter = 0;
            std::optional<bool> updated;
    };
}


#endif //LIBCOMMON_FIELD_HPP
