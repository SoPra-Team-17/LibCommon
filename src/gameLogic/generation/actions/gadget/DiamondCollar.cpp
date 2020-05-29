//
// Created by Carolin on 08.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateDiamondCollar(const State &s, const util::UUID &activeCharacter,
                                           const spy::MatchConfig &config) {
        std::vector<std::shared_ptr<BaseOperation>> valid_ops;

        GadgetAction action{false, s.getCatCoordinates().value(), activeCharacter,
                            gadget::GadgetEnum::DIAMOND_COLLAR};
        bool valid = ActionValidator::validateGadgetAction(s, action, config);

        if (valid) {
            valid_ops.push_back(std::make_shared<GadgetAction>(action));
        }

        return valid_ops;
    }
}