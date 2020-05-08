//
// Created by Carolin on 07.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateAllGadgetActions(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement
        return {nullptr};
    }

    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateGadgetActions(const State &s, const util::UUID &activeCharacter,
                                           gadget::GadgetEnum /*gadget*/) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0) {
            return {};
        }

        // TODO implement: switch gadget
        return {nullptr};
    }
}