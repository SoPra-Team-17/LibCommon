//
// Created by jonas on 07.04.20.
//

#include "EquipmentChoice.hpp"

namespace spy::network::messages {
    void to_json(nlohmann::json &j, const EquipmentChoice &e) {
        MessageContainer::common_to_json(j, e);
        j["chosenCharacterIds"] = e.chosenCharacterIds;
        j["chosenGadgets"] = e.chosenGadgets;
    }

    void from_json(const nlohmann::json &j, EquipmentChoice &e) {
        MessageContainer::common_from_json(j, e);
        j.at("chosenCharacterIds").get_to(e.chosenCharacterIds);
        j.at("chosenGadgets").get_to(e.chosenGadgets);
    }

    std::vector<util::UUID> &EquipmentChoice::getChosenCharacterIds() {
        return chosenCharacterIds;
    }

    std::vector<gadget::GadgetEnum> &EquipmentChoice::getChosenGadgets() {
        return chosenGadgets;
    }

    EquipmentChoice::EquipmentChoice() : MessageContainer{MessageTypeEnum::EQUIPMENT_CHOICE, {}} {}

    EquipmentChoice::EquipmentChoice(util::UUID playerId) :
            MessageContainer{MessageTypeEnum::EQUIPMENT_CHOICE, playerId} {}
}