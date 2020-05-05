/**
 * @file   Field.cpp
 * @author Dominik Authaler
 * @date   09.04.2020 (creation)
 * @brief  Definition of the field class.
 */

#include "Field.hpp"
#include "util/OptionalSerialization.hpp"
#include "util/GadgetSerialization.hpp"

namespace spy::scenario {

    Field::Field(FieldStateEnum fieldState) : state(fieldState) {}

    void Field::setFieldState(FieldStateEnum fieldState) {
        Field::state = fieldState;

        if (fieldState != FieldStateEnum::ROULETTE_TABLE) {
            Field::inverted.reset();
            Field::destroyed.reset();
            Field::chipAmount.reset();
        }

        if (fieldState != FieldStateEnum::SAFE) {
            Field::safeIndex.reset();
        }

        Field::updated = true;
    }

    void Field::setDestroyed(std::optional<bool> isDestroyed) {
        if (Field::state != FieldStateEnum::ROULETTE_TABLE) {
            throw std::invalid_argument("Field has no roulette table!");
        }
        Field::destroyed = isDestroyed;

        Field::updated = true;
    }

    void Field::setUpdated(std::optional<bool> isUpdated) {
        Field::updated = isUpdated;
    }

    void Field::setFoggy(bool isFoggy) {
        Field::foggy = isFoggy;

        Field::updated = true;
    }

    void Field::incrementFogCounter() {
        Field::fogCounter++;
    }

    void Field::resetFogCounter() {
        Field::fogCounter = 0;
    }

    void Field::setGadget(std::optional<std::shared_ptr<Gadget>> g) {
        Field::gadget = g;

        Field::updated = true;
    }

    void Field::removeGadget() {
        Field::gadget.reset();

        Field::updated = true;
    }


    void Field::setChipAmount(std::optional<unsigned int> chips) {
        if (Field::state != FieldStateEnum::ROULETTE_TABLE) {
            throw std::invalid_argument("Field has no roulette table!");
        }
        Field::chipAmount = chips;

        Field::updated = true;
    }

    void Field::setSafeIndex(std::optional<unsigned int> index) {
        if (Field::state != FieldStateEnum::SAFE) {
            throw std::invalid_argument("Field has no safe!");
        }
        Field::safeIndex = index;

        Field::updated = true;
    }

    void Field::setInverted(std::optional<bool> isInverted) {
        if (Field::state != FieldStateEnum::ROULETTE_TABLE) {
            throw std::invalid_argument("Field has no roulette table!");
        }
        Field::inverted = isInverted;

        Field::updated = true;
    }

    FieldStateEnum Field::getFieldState() const {
        return state;
    }

    std::optional<bool> Field::isDestroyed() const {
        return destroyed;
    }

    std::optional<bool> Field::isUpdated() const {
        return updated;
    }

    std::optional<bool> Field::isInverted() const {
        return inverted;
    }

    bool Field::isFoggy() const {
        return foggy;
    }

    [[nodiscard]] unsigned int Field::getFogCounter() const {
        return fogCounter;
    }

    const std::optional<std::shared_ptr<spy::gadget::Gadget>> &Field::getGadget() const {
        return gadget;
    }

    std::optional<unsigned int> Field::getChipAmount() const {
        return chipAmount;
    }

    std::optional<unsigned int> Field::getSafeIndex() const {
        return safeIndex;
    }

    void to_json(nlohmann::json &j, const Field &f) {
        j["state"] = f.state;
        j["gadget"] = f.gadget;
        j["isDestroyed"] = f.destroyed;
        j["isInverted"] = f.inverted;
        j["chipAmount"] = f.chipAmount;
        j["safeIndex"] = f.safeIndex;
        j["isFoggy"] = f.foggy;
        j["isUpdated"] = f.updated;
    }

    void from_json(const nlohmann::json &j, Field &f) {
        j.at("state").get_to(f.state);

        if (j.find("gadget") != j.end()) {
            j.at("gadget").get_to(f.gadget);
        }

        if (f.state == FieldStateEnum::ROULETTE_TABLE) {
            if (j.find("isDestroyed") != j.end()) {
                j.at("isDestroyed").get_to(f.destroyed);
            }

            if (j.find("isInverted") != j.end()) {
                j.at("isInverted").get_to(f.inverted);
            }

            if (j.find("chipAmount") != j.end()) {
                j.at("chipAmount").get_to(f.chipAmount);
            }
        } else if (f.state == FieldStateEnum::SAFE && j.find("safeIndex") != j.end()) {
            j.at("safeIndex").get_to(f.safeIndex);
        }

        j.at("isFoggy").get_to(f.foggy);

        if (j.find("isUpdated") != j.end()) {
            j.at("isUpdated").get_to(f.updated);
        }
    }

    bool Field::operator==(const Field &rhs) const {
        return std::tie(state, gadget, destroyed, inverted, chipAmount, safeIndex, foggy, updated) ==
               std::tie(rhs.state, rhs.gadget, rhs.destroyed, rhs.inverted, rhs.chipAmount, rhs.safeIndex, rhs.foggy,
                        rhs.updated);
    }
}
