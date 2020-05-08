//
// Created by Carolin on 07.05.2020.
//

#ifndef LIBCOMMON_ITEMCHOICEGENERATOR_HPP
#define LIBCOMMON_ITEMCHOICEGENERATOR_HPP


#include <util/UUID.hpp>
#include <vector>
#include <variant>
#include <datatypes/gadgets/GadgetEnum.hpp>

namespace spy::gameplay {
    class ItemChoiceGenerator {
        public:
            ItemChoiceGenerator() = delete;

            static std::variant<util::UUID, gadget::GadgetEnum>
            getRandomItemChoice(const std::vector<util::UUID>& offeredCharacterIds,
                                const std::vector<spy::gadget::GadgetEnum>& offeredGadgets);
    };
}


#endif //LIBCOMMON_ITEMCHOICEGENERATOR_HPP
