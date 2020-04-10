//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_ITEMCHOICE_HPP
#define LIBCOMMON_ITEMCHOICE_HPP

#include <network/MessageContainer.hpp>
#include <datatypes/gadgets/GadgetEnum.hpp>
#include <variant>

namespace spy::network::messages {

    /**
     * @brief Represents choice of either a spy::character::Character (by util::UUID) or a spy::gadget::Gadget
     */
    class ItemChoice : public MessageContainer {
        public:
            ItemChoice();

            /**
             * @param choice Character or Gadget
             */
            ItemChoice(const util::UUID &playerId, std::variant<util::UUID, gadget::GadgetEnum> choice);

            [[nodiscard]] const std::variant<util::UUID, gadget::GadgetEnum> &getChoice() const;

            friend void to_json(nlohmann::json &j, const ItemChoice &i);

            friend void from_json(const nlohmann::json &j, ItemChoice &i);

        private:
            std::variant<util::UUID, gadget::GadgetEnum> choice;
    };
}


#endif //LIBCOMMON_ITEMCHOICE_HPP
