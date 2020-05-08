//
// Created by Carolin on 07.05.2020.
//

#include "EquipmentChoiceGenerator.hpp"

namespace spy::gameplay {

    std::map<util::UUID, std::set<gadget::GadgetEnum>>
    EquipmentChoiceGenerator::getRandomEquipmentChoice(const std::vector<util::UUID>& /*chosenCharacterIds*/,
                                                       const std::vector<spy::gadget::GadgetEnum>& /*chosenGadgets*/) {
        // TODO implement
        return std::map<util::UUID, std::set<gadget::GadgetEnum>>();
    }
}