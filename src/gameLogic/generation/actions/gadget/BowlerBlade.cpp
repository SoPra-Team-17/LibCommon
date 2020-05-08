/**
 * @file   Cocktail.cpp
 * @author Marco Deuscher (code), Carolin (created)
 * @date   08.05.2020 (creation)
 * @brief  Implementation of bowler blade gadget action generation
 */

#include "gameLogic/generation/ActionGenerator.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateBowlerBlade(const State &s, const util::UUID &activeCharacter,
                                         const spy::MatchConfig &config) {
        std::vector<std::shared_ptr<BaseOperation>> valid_ops;

        for (const auto &targetChar : s.getCharacters()) {
            if (targetChar.getCoordinates().has_value()) {
                auto action = std::make_shared<GadgetAction>(false, targetChar.getCoordinates().value(),
                                                             activeCharacter,
                                                             gadget::GadgetEnum::BOWLER_BLADE);
                bool valid = ActionValidator::validate(s, action, config);
                if (valid) {
                    valid_ops.push_back(action);
                }
            }
        }

        return valid_ops;
    }
}