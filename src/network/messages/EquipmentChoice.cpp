//
// Created by jonas on 07.04.20.
//

#include "EquipmentChoice.hpp"

#include <utility>

namespace spy::network::messages {
    void to_json(nlohmann::json &j, const EquipmentChoice &e) {
        MessageContainer::common_to_json(j, e);
        j["equipment"] = e.equipment;
    }

    void from_json(const nlohmann::json &j, EquipmentChoice &e) {
        MessageContainer::common_from_json(j, e);
        j.at("equipment").get_to(e.equipment);
    }

    EquipmentChoice::EquipmentChoice() : MessageContainer{MessageTypeEnum::EQUIPMENT_CHOICE, {}} {}

    EquipmentChoice::EquipmentChoice(util::UUID clientId, std::map<util::UUID, std::set<gadget::GadgetEnum>> equipment)
            : MessageContainer{MessageTypeEnum::EQUIPMENT_CHOICE, clientId},
              equipment{std::move(equipment)} {}

    auto EquipmentChoice::getEquipment() const -> const std::map<util::UUID, std::set<gadget::GadgetEnum>> & {
        return equipment;
    }

    bool EquipmentChoice::operator==(const EquipmentChoice &rhs) const {
        return isEqual(rhs) && equipment == rhs.equipment;
    }

    bool EquipmentChoice::validate(RoleEnum playerRole, std::vector<util::UUID> chosenCharacter,
                                   std::vector<gadget::GadgetEnum> chosenGadget) const {
        if (playerRole == spy::network::RoleEnum::INVALID ||
            playerRole == spy::network::RoleEnum::SPECTATOR) {
            return false;
        }

        std::vector<util::UUID> mapCharacters;
        std::vector<gadget::GadgetEnum> mapGadgets;

        for (const auto &[character, gadgets] : equipment) {
            // check if character is part of the chosen ones
            auto charIt = std::find(chosenCharacter.begin(), chosenCharacter.end(), character);
            if (charIt == chosenCharacter.end()) {
                return false;
            }

            // check if the gadget set is part of the chosen ones
            for (const auto &g : gadgets) {
                auto gadgetIt = std::find(chosenGadget.begin(), chosenGadget.end(), g);
                if (gadgetIt == chosenGadget.end()) {
                    return false;
                } else {
                    *gadgetIt = spy::gadget::GadgetEnum::INVALID;
                }
            }
        }

        return true;
    }
}