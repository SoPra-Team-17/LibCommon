//
// Created by jonas on 07.04.20.
//

#include "EquipmentChoice.hpp"

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

    EquipmentChoice::EquipmentChoice(util::UUID playerId) :
            MessageContainer{MessageTypeEnum::EQUIPMENT_CHOICE, playerId} {}

    auto EquipmentChoice::getEquipment() const -> const std::map<util::UUID, std::set<gadget::GadgetEnum>> & {
        return equipment;
    }
}