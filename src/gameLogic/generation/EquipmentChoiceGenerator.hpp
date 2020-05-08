//
// Created by Carolin on 07.05.2020.
//

#ifndef LIBCOMMON_EQUIPMENTCHOICEGENERATOR_HPP
#define LIBCOMMON_EQUIPMENTCHOICEGENERATOR_HPP

#include <util/UUID.hpp>
#include <map>
#include <set>
#include <datatypes/gadgets/GadgetEnum.hpp>

namespace spy::gameplay {
    class EquipmentChoiceGenerator {
        public:
            EquipmentChoiceGenerator() = delete;

            static std::map <util::UUID, std::set<gadget::GadgetEnum>>
            getRandomEquipmentChoice(const std::vector <util::UUID>& chosenCharacterIds,
                                     const std::vector <spy::gadget::GadgetEnum>& chosenGadgets);
    };
}


#endif //LIBCOMMON_EQUIPMENTCHOICEGENERATOR_HPP
