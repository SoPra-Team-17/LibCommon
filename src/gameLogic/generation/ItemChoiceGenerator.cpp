//
// Created by Carolin on 07.05.2020.
//

#include "ItemChoiceGenerator.hpp"

namespace spy::gameplay {

    std::variant<util::UUID, gadget::GadgetEnum>
    ItemChoiceGenerator::getRandomItemChoice(const std::vector<util::UUID>& /*offeredCharacterIds*/,
                                             const std::vector<spy::gadget::GadgetEnum>& /*offeredGadgets*/) {
        // TODO implement
        return std::variant<util::UUID, gadget::GadgetEnum>();
    }
}