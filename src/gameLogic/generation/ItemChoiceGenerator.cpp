//
// Created by Carolin on 07.05.2020.
//

#include "ItemChoiceGenerator.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    std::variant<util::UUID, gadget::GadgetEnum>
    ItemChoiceGenerator::getRandomItemChoice(const std::vector<util::UUID>& offeredCharacterIds,
                                             const std::vector<spy::gadget::GadgetEnum>& offeredGadgets) {


        if (!offeredCharacterIds.empty() && !offeredGadgets.empty()) {
            auto character = util::GameLogicUtils::getRandomItemFromContainer(offeredCharacterIds);
            auto gadget = util::GameLogicUtils::getRandomItemFromContainer(offeredGadgets);
            auto r = util::GameLogicUtils::probabilityTest(0.5);
            if (r) {
                return std::variant<util::UUID, gadget::GadgetEnum>(*character);
            } else {
                return std::variant<util::UUID, gadget::GadgetEnum>(*gadget);
            }
        }
        if(offeredCharacterIds.empty()) {
            return std::variant<util::UUID, gadget::GadgetEnum>(*util::GameLogicUtils::getRandomItemFromContainer(offeredGadgets));
        }
        if (offeredGadgets.empty()) {
            return std::variant<util::UUID, gadget::GadgetEnum>(*util::GameLogicUtils::getRandomItemFromContainer(offeredCharacterIds));
        }
        
        throw std::domain_error("offeredCharacterIds and offeredGadgets were empty");
    }
}