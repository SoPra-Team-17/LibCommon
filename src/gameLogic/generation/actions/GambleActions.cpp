//
// Created by Carolin on 07.05.2020.
//

#include <util/GameLogicUtils.hpp>
#include <gameLogic/validation/ActionValidator.hpp>
#include <datatypes/gameplay/GambleAction.hpp>
#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateGambleActions(const State &s, const util::UUID &activeCharacter, const double chipPercentage) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0 || character->getChips() == 0) {
            return {};
        }

        std::vector<std::shared_ptr<BaseOperation>> valid_ops;
        auto points = util::GameLogicUtils::getNearFieldsInDist(s, character->getCoordinates().value(), 1,
                                                                [](const util::Point &/*p*/) {
                                                                    return true;
                                                                });

        for (auto &p: points.first) {
            GambleAction action {false, p, activeCharacter, 0};
            bool valid = ActionValidator::validateGambleAction(s, action);
            if (valid) {
                valid_ops.push_back(std::make_shared<GambleAction>(action));
            }
        }

        for (auto &op: valid_ops) {
            auto stake = std::min((int)s.getMap().getField(op->getTarget()).getChipAmount().value(),
                                  (int)std::ceil(chipPercentage * character->getChips()));
            std::dynamic_pointer_cast<GambleAction>(op)->setStake(stake);
        }

        return valid_ops;
    }
}
