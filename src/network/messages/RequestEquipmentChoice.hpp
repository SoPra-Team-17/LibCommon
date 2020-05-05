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

            RequestEquipmentChoice(const util::UUID &clientId,
                                   std::vector<util::UUID> chosenCharacterIds,
                                   std::vector<gadget::GadgetEnum> chosenGadgets);

            [[nodiscard]] auto getChosenCharacterIds() const -> const std::vector<util::UUID> &;

            [[nodiscard]] auto getChosenGadgets() const -> const std::vector<spy::gadget::GadgetEnum> &;

            friend void to_json(nlohmann::json &j, const RequestEquipmentChoice &r);

            friend void from_json(const nlohmann::json &j, RequestEquipmentChoice &r);

            bool operator==(const RequestEquipmentChoice &rhs) const;

        private:
            std::vector<util::UUID> chosenCharacterIds;
            std::vector<spy::gadget::GadgetEnum> chosenGadgets;
    };

}

#endif //LIBCOMMON_REQUESTEQUIPMENTCHOICE_HPP
