/**
 * @file   Field.cpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Definition of the field class.
 */

#include "Field.hpp"

namespace spy::scenario {

    Field::Field(FieldStateEnum fieldState) : state(fieldState) {}

    void Field::setFieldState(FieldStateEnum fieldState) {
        Field::state = fieldState;
    }

    /**
     * Setter for the state of the roulette table on this field.
     * @param isDestroyed State of the roulette table.
     * @note  This param can only be set if the field state is ROULETTE_TABLE.
     */
    void Field::setDestroyed(std::optional<bool> isDestroyed) {
        if (Field::state != FieldStateEnum::ROULETTE_TABLE) {
            throw std::invalid_argument("Field has no roulette table!");
        }
        Field::destroyed = isDestroyed;
    }

    void Field::setUpdated(std::optional<bool> isUpdated) {
        Field::updated = isUpdated;
    }

    void Field::setFoggy(bool isFoggy) {
        Field::foggy = isFoggy;
    }

    void Field::setGadget(std::optional<Gadget> g) {
        Field::gadget = g;
    }

    /**
     * Setter for the chip amount of the roulette table on this field.
     * @param chips Chip amount.
     * @note  This param can only be set if the field state is ROULETTE_TABLE.
     */
    void Field::setChipAmount(std::optional<unsigned int> chips) {
        if (Field::state != FieldStateEnum::ROULETTE_TABLE) {
            throw std::invalid_argument("Field has no roulette table!");
        }
        Field::chipAmount = chips;
    }

    /**
     * Setter for the index of the safe on this field.
     * @param index Safe index.
     * @note  This param can only be set if the field state is SAFE.
     */
    void Field::setSafeIndex(std::optional<unsigned int> index) {
        if (Field::state != FieldStateEnum::SAFE) {
            throw std::invalid_argument("Field has no safe!");
        }
        Field::safeIndex = index;
    }

    /**
     * Setter for the inversion of the roulette table on this field.
     * @param isInverted Inversion state of the roulette table.
     * @note  This param can only be set if the field state is ROULETTE_TABLE.
     */
    void Field::setInverted(std::optional<bool> isInverted) {
        if (Field::state != FieldStateEnum::ROULETTE_TABLE) {
            throw std::invalid_argument("Field has no roulette table!");
        }
        Field::inverted = isInverted;
    }

    FieldStateEnum Field::getFieldState() const {
        return state;
    }

    /**
     * Getter for the state of the roulette table.
     * @return True if the roulette table is destroyed, else false.
     * @note   The return value only contains a value if the field's state is ROULETTE_TABLE.
     */
    std::optional<bool> Field::isDestroyed() const {
        return destroyed;
    }

    std::optional<bool> Field::isUpdated() const {
        return updated;
    }

    /**
     * Getter for the inversion of the roulette table probabilities.
     * @return True if the roulette table is inverted, else false.
     * @note   The return value only contains a value if the field's state is ROULETTE_TABLE.
     */
    std::optional<bool> Field::isInverted() const {
        return inverted;
    }

    bool Field::isFoggy() const {
        return foggy;
    }

    const std::optional<spy::gadget::Gadget> &Field::getGadget() const {
        return gadget;
    }

    /**
     * Getter for the amount of chips of the roulette table.
     * @return Chip amount.
     * @note   The return value only contains a value if the field's state is ROULETTE_TABLE.
     */
    std::optional<unsigned int> Field::getChipAmount() const {
        return chipAmount;
    }

    /**
     * Getter for the index of the safe.
     * @return Safe index.
     * @note   The return value only contains a value if the field's state is SAFE.
     */
    std::optional<unsigned int> Field::getSafeIndex() const {
        return safeIndex;
    }
}
