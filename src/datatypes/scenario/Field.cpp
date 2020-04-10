/**
 * @file   Field.cpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Definition of the field class.
 */

#include "Field.hpp"

namespace spy::scenario {

    Field::Field(FieldStateEnum fieldState) {
        Field::state = fieldState;
    }

    void Field::setFieldState(FieldStateEnum fieldState) {
        Field::state = fieldState;
    }

    void Field::setDestroyed(bool isDestroyed) {
        Field::destroyed = isDestroyed;
    }

    void Field::setUpdated(bool isUpdated) {
        Field::updated = isUpdated;
    }

    void Field::setFoggy(bool isFoggy) {
        Field::foggy = isFoggy;
    }

    void Field::setGadget(std::optional<Gadget> g) {
        Field::gadget = g;
    }

    void Field::setChipAmount(std::optional<unsigned int> chips) {
        Field::chipAmount = chips;
    }

    void Field::setSafeIndex(std::optional<unsigned int> index) {
        Field::safeIndex = index;
    }

    void Field::setInverted(bool isInverted) {
        Field::inverted = isInverted;
    }

    FieldStateEnum Field::getFieldState() const {
        return state;
    }

    bool Field::isDestroyed() const {
        return destroyed;
    }

    bool Field::isUpdated() const {
        return updated;
    }

    bool Field::isInverted() const {
        return inverted;
    }

    bool Field::isFoggy() const {
        return foggy;
    }

    const std::optional<spy::gadget::Gadget> &Field::getGadget() const {
        return gadget;
    }

    std::optional<unsigned int> Field::getChipAmount() const {
        return chipAmount;
    }

    std::optional<unsigned int> Field::getSafeIndex() const {
        return safeIndex;
    }
}
