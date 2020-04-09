//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_EQUIPMENTCHOICE_HPP
#define LIBCOMMON_EQUIPMENTCHOICE_HPP

#include <network/MessageContainer.hpp>
#include <datatypes/gadgets/GadgetEnum.hpp>

namespace spy::network::messages {
    class EquipmentChoice : public MessageContainer {
        public:

            EquipmentChoice();

            explicit EquipmentChoice(util::UUID playerId);

            std::vector<util::UUID> &getChosenCharacterIds();

            std::vector<gadget::GadgetEnum> &getChosenGadgets();

            friend void to_json(nlohmann::json &j, const EquipmentChoice &e);

            friend void from_json(const nlohmann::json &j, EquipmentChoice &e);

        private:
            std::vector<util::UUID> chosenCharacterIds;
            std::vector<gadget::GadgetEnum> chosenGadgets;
    };
}
#endif //LIBCOMMON_EQUIPMENTCHOICE_HPP
