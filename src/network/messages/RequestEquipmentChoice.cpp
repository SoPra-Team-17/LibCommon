//
// Created by marco on 10.04.20.
//

#include "RequestEquipmentChoice.hpp"

#include <utility>

namespace spy::network::messages {

    RequestEquipmentChoice::RequestEquipmentChoice() : MessageContainer{MessageTypeEnum::REQUEST_EQUIPMENT_CHOICE,
                                                                        {}} {}

    RequestEquipmentChoice::RequestEquipmentChoice(const util::UUID &playerId,
                                                   std::vector<util::UUID> chosenCharacterIds,
                                                   std::vector<gadget::GadgetEnum> chosenGadgets) :
            MessageContainer{MessageTypeEnum::REQUEST_EQUIPMENT_CHOICE, playerId},
            chosenCharacterIds{std::move(chosenCharacterIds)},
            chosenGadgets{std::move(chosenGadgets)} {}


    void to_json(nlohmann::json &j, const RequestEquipmentChoice &r) {
        MessageContainer::common_to_json(j, r);
        j["chosenCharacterIds"] = r.chosenCharacterIds;
        j["chosenGadgets"] = r.chosenGadgets;
    }

    void from_json(const nlohmann::json &j, RequestEquipmentChoice &r) {
        MessageContainer::common_from_json(j, r);
        j.at("chosenCharacterIds").get_to(r.chosenCharacterIds);
        j.at("chosenGadgets").get_to(r.chosenGadgets);
    }

    auto RequestEquipmentChoice::getChosenCharacterIds() const -> const std::vector<util::UUID> & {
        return chosenCharacterIds;
    }

    auto RequestEquipmentChoice::getChosenGadgets() const -> const std::vector<spy::gadget::GadgetEnum> & {
        return chosenGadgets;
    }

}