//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_EQUIPMENTCHOICE_HPP
#define LIBCOMMON_EQUIPMENTCHOICE_HPP

#include <network/MessageContainer.hpp>
#include <datatypes/gadgets/GadgetEnum.hpp>
#include <map>
#include <set>
#include <network/RoleEnum.hpp>

namespace spy::network::messages {
    class EquipmentChoice : public MessageContainer {
        public:

            EquipmentChoice();

            explicit EquipmentChoice(util::UUID playerId, std::map<util::UUID, std::set<gadget::GadgetEnum>> equipment);

            [[nodiscard]] auto getEquipment() const -> const std::map<util::UUID, std::set<gadget::GadgetEnum>> &;

            friend void to_json(nlohmann::json &j, const EquipmentChoice &e);

            friend void from_json(const nlohmann::json &j, EquipmentChoice &e);

            bool operator==(const EquipmentChoice &rhs) const;

            /**
             * validate message according role and if player is known
             * @param playerRole role of the player who sent the message
             * @param chosenCharacter list of character ids that were chosen player
             * @param chosenGadget list of gadget types that were chosen by player
             * @return true if message is valid
             *         false if message is not valid
             */
            [[nodiscard]] bool validate(const RoleEnum &playerRole, const std::vector<spy::util::UUID> &chosenCharacter,
                                        const std::vector<spy::gadget::GadgetEnum> &chosenGadget) const;

        private:
            std::map<util::UUID, std::set<gadget::GadgetEnum>> equipment;
    };
}
#endif //LIBCOMMON_EQUIPMENTCHOICE_HPP
