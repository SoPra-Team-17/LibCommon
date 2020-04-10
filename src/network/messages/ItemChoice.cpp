//
// Created by marco on 10.04.20.
//

#include "ItemChoice.hpp"

namespace spy::network::messages {

    ItemChoice::ItemChoice() : MessageContainer(MessageTypeEnum::ITEM_CHOICE, {}) {}

    ItemChoice::ItemChoice(const util::UUID &playerId, const util::UUID &chosenCharacter,
                           const spy::gadget::GadgetEnum &chosenGadget) : MessageContainer(MessageTypeEnum::ITEM_CHOICE,
                                                                                           playerId),
                                                                          chosenCharacter(chosenCharacter),
                                                                          chosenGadget(chosenGadget) {}


    void to_json(nlohmann::json &j, const ItemChoice &i) {
        MessageContainer::common_to_json(j, i);
        j["chosenCharacter"] = i.chosenCharacter;
        j["chosenGadget"] = i.chosenGadget;
    }

    void from_json(const nlohmann::json &j, ItemChoice &i) {
        MessageContainer::common_from_json(j, i);
        j.at("chosenCharacter").get_to(i.chosenCharacter);
        j.at("chosenGadget").get_to(i.chosenGadget);
    }

    const util::UUID &ItemChoice::getChosenCharacter() const {
        return chosenCharacter;
    }

    const spy::gadget::GadgetEnum &ItemChoice::getChosenGadget() const {
        return chosenGadget;
    }
}
