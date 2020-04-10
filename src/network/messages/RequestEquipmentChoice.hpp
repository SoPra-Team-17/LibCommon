//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_REQUESTEQUIPMENTCHOICE_HPP
#define LIBCOMMON_REQUESTEQUIPMENTCHOICE_HPP

#include <network/MessageContainer.hpp>
#include <datatypes/gadgets/GadgetEnum.hpp>

namespace spy::network::messages {

    class RequestEquipmentChoice : public MessageContainer {
        public:

            RequestEquipmentChoice();

            explicit RequestEquipmentChoice(const util::UUID &playerId);

            [[nodiscard]] auto getChosenCharacterIds() const -> const std::vector<util::UUID> &;

            [[nodiscard]] auto getChosenGadgets() const -> const std::vector<spy::gadget::GadgetEnum> &;

            friend void to_json(nlohmann::json &j, const RequestEquipmentChoice &r);

            friend void from_json(const nlohmann::json &j, RequestEquipmentChoice &r);

        private:
            std::vector<util::UUID> chosenCharacterIds;
            std::vector<spy::gadget::GadgetEnum> chosenGadgets;
    };

}

#endif //LIBCOMMON_REQUESTEQUIPMENTCHOICE_HPP
