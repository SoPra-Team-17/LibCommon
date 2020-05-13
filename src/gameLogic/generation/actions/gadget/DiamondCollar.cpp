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

        auto action = std::make_shared<GadgetAction>(false, s.getCatCoordinates().value(), activeCharacter,
                                                     gadget::GadgetEnum::DIAMOND_COLLAR);
        bool valid = ActionValidator::validate(s, action, config);

        if (valid) {
            valid_ops.push_back(action);
        }

        return valid_ops;
    }
}