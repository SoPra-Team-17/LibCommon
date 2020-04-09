//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_EQUIPMENTCHOICE_HPP
#define LIBCOMMON_EQUIPMENTCHOICE_HPP

#include <network/MessageContainer.hpp>
#include <datatypes/gadgets/GadgetEnum.hpp>
#include <map>
#include <set>

namespace spy::network::messages {
    class EquipmentChoice : public MessageContainer {
        public:

            EquipmentChoice();

            explicit EquipmentChoice(util::UUID playerId);

            [[nodiscard]] auto getEquipment() const -> const std::map<util::UUID, std::set<gadget::GadgetEnum>> &;

            friend void to_json(nlohmann::json &j, const EquipmentChoice &e);

            friend void from_json(const nlohmann::json &j, EquipmentChoice &e);

        private:
            std::map<util::UUID, std::set<gadget::GadgetEnum>> equipment;
    };
}
#endif //LIBCOMMON_EQUIPMENTCHOICE_HPP
