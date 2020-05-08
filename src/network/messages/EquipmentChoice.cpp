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
            mapCharacters.push_back(character);
            mapGadgets.insert(mapGadgets.end(), gadgets.begin(), gadgets.end());
        }

        std::sort(chosenCharacter.begin(), chosenCharacter.end());
        std::sort(mapCharacters.begin(), mapCharacters.end());
        std::sort(chosenGadget.begin(), chosenGadget.end());
        std::sort(mapGadgets.begin(), mapGadgets.end());

        return (chosenCharacter == mapCharacters && chosenGadget == mapGadgets);
    }
}