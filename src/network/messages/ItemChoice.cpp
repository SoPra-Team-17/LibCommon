//
// Created by marco on 10.04.20.
//

#include "ItemChoice.hpp"

namespace spy::network::messages {

    ItemChoice::ItemChoice() : MessageContainer(MessageTypeEnum::ITEM_CHOICE, {}) {}

    ItemChoice::ItemChoice(const util::UUID &clientId, std::variant<util::UUID, gadget::GadgetEnum> choice) :
            MessageContainer(MessageTypeEnum::ITEM_CHOICE, clientId),
            choice(choice) {}

    void to_json(nlohmann::json &j, const ItemChoice &i) {
        MessageContainer::common_to_json(j, i);
        if (std::holds_alternative<util::UUID>(i.choice)) {
            j["chosenCharacter"] = std::get<util::UUID>(i.choice);
            j["chosenGadget"] = nullptr;
        } else {
            j["chosenGadget"] = std::get<gadget::GadgetEnum>(i.choice);
            j["chosenCharacter"] = nullptr;
        }
    }

    void from_json(const nlohmann::json &j, ItemChoice &i) {
        MessageContainer::common_from_json(j, i);
        auto chosenCharacter = j.find("chosenCharacter");
        if (chosenCharacter != j.end() && !chosenCharacter->is_null()) {
            i.choice = j.at("chosenCharacter").get<util::UUID>();
        } else {
            i.choice = j.at("chosenGadget").get<gadget::GadgetEnum>();
        }
    }

    const std::variant<util::UUID, gadget::GadgetEnum> &ItemChoice::getChoice() const {
        return choice;
    }

    bool ItemChoice::operator==(const ItemChoice &rhs) const {
        return isEqual(rhs) &&
               choice == rhs.choice;
    }

    bool ItemChoice::validate(RoleEnum playerRole, std::vector<util::UUID> offeredCharacters,
                              std::vector<gadget::GadgetEnum> offeredGadgets) const {
        if (playerRole == spy::network::RoleEnum::INVALID ||
            playerRole == spy::network::RoleEnum::SPECTATOR) {
            return false;
        }

        if (std::holds_alternative<util::UUID>(choice)) {
            if (std::find(offeredCharacters.begin(), offeredCharacters.end(), std::get<util::UUID>(choice)) ==
                offeredCharacters.end()) {
                return false;
            }
        } else if (std::holds_alternative<gadget::GadgetEnum>(choice)) {
            if (std::find(offeredGadgets.begin(), offeredGadgets.end(), std::get<gadget::GadgetEnum>(choice)) ==
                offeredGadgets.end()) {
                return false;
            }
        } else {
            return false;
        }

        return true;
    }
}
