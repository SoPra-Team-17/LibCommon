//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_ITEMCHOICE_HPP
#define LIBCOMMON_ITEMCHOICE_HPP

#include <network/MessageContainer.hpp>
#include <datatypes/gadgets/GadgetEnum.hpp>

namespace spy::network::messages {

    class ItemChoice : public MessageContainer {
        public:
            ItemChoice();

            ItemChoice(const util::UUID &playerId, const util::UUID &chosenCharacter,
                       const spy::gadget::GadgetEnum &chosenGadger);

            [[nodiscard]] const util::UUID &getChosenCharacter() const;

            [[nodiscard]] const gadget::GadgetEnum &getChosenGadget() const;

            friend void to_json(nlohmann::json &j, const ItemChoice &i);

            friend void from_json(const nlohmann::json &j, ItemChoice &i);


        private:
            util::UUID chosenCharacter;
            spy::gadget::GadgetEnum chosenGadget;
    };
}


#endif //LIBCOMMON_ITEMCHOICE_HPP
